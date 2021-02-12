/* 
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

   3
  7 4
 2 4 6
8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom of the triangle below:

                            75
                          95 64
                        17 47 82
                      18 35 87 10
                    20 04 82 47 65
                  19 01 23 75 03 34
                88 02 77 73 07 63 67
              99 65 04 28 06 16 70 92
            41 41 26 56 83 40 80 70 33
          41 48 72 33 47 32 37 16 94 29
        53 71 44 65 25 43 91 52 97 51 14
      70 11 33 28 77 73 17 78 39 68 17 57
    91 71 52 38 17 14 91 43 58 50 27 29 48
  63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
*/

#include "UsefulFunctions.h"
void printPyramid(std::vector<std::string> string_pyramid, std::vector<int> boldIndices = {})
{
    int count{0};
    int pyramid_level{1};
    while (count < string_pyramid.size())
    {
        for (int j{(int)string_pyramid.size() / 8 - pyramid_level}; j >= 0; --j)
        {
            std::cout << "  ";
        }
        for (int j{1}; j <= pyramid_level; ++j)
        {
            if (std::find(boldIndices.begin(),boldIndices.end(), count) != boldIndices.end())
            std::cout << UsefulFunctions::boldText(string_pyramid[count++]) << " ";
            else
            std::cout << string_pyramid[count++] << " ";
        }
        std::cout << "\n";
        ++pyramid_level;
    }
}

template <typename T>
std::vector<std::size_t> sort_indices(const std::vector<T> &v, bool ascending = 1)
{
    // initialize original index locations
    std::vector<std::size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    // using std::stable_sort instead of std::sort
    // to avoid unnecessary index re-orderings
    // when v contains elements of equal values
    if (ascending)
    {
        stable_sort(idx.begin(), idx.end(),
                    [&v](std::size_t i1, std::size_t i2) { return v[i1] < v[i2]; });
    }
    else
    {
        stable_sort(idx.begin(), idx.end(),
                    [&v](std::size_t i1, std::size_t i2) { return v[i1] > v[i2]; });
    }

    return idx;
}

int main()
{
    // Load file
    std::string filepath("numbers.txt");
    std::ifstream infile{UsefulFunctions::loadFile(filepath)};
    // Put numbers into a vector
    std::vector<int> number_pyramid;         // For calculations
    std::vector<std::string> string_pyramid; // For the display
    std::string num_string;
    while (infile >> num_string)
    {
        number_pyramid.push_back(std::stoi(num_string));
        string_pyramid.push_back(num_string);
    }

    // The number of numbers in the pyramid.
    std::size_t num_numbers{number_pyramid.size()};
    // Visualise the pyramid
    printPyramid(string_pyramid);
    std::cout << "\n";

    // Sorted (descending) pyramid numbers and indices
    std::vector<int> sorted_pyramid{number_pyramid};
    std::vector<std::size_t> sorted_indices{sort_indices(number_pyramid, 0)};

    std::sort(sorted_pyramid.begin(), sorted_pyramid.end(), std::greater<int>());

    // Idea:
    // For the first 0:n elements in sorted_indices, determine for the smallest n whether a path can be taken from the top to the bottom.
    // This probably won't just be the highest numbers as others must be used, like index 0 (top number)

    // Define the layers of the pyramid by the index of the last element on a layer. Should be (the triangle numbers - 1): {0,2,5,9,14,...} a.k.a pyramid numbers amiright
    std::vector<int> define_layers;
    for (long j{0}, k{1}; j < number_pyramid.size(); j += ++k)
    {
        define_layers.push_back(j);
    }

    // To check whether two indices are in adjacent layers, refer to define_layers
    // To check whether two adjacent indices A and B can be connected: Let index A be in layer N and B in layer N+1 (Layers start at 0);
    // They are connected if B == A+N+1 or B == A+N+2.

    // A vector that says which layer of the pyramid an index is in. The top layer is 0.
    std::vector<int> which_layer(num_numbers, 0);
    for (int j{1}; j < num_numbers; ++j)
    {
        for (int k{0}; k < define_layers.size(); ++k)
        {
            if ((j > define_layers[std::max(k - 1, 0)]) && (j <= define_layers[k]))
            {
                which_layer[j] = k;
                break;
            }
        }
    }

    // A lambda that determines whether indices are connected. Index i is connected to index j if isConnected(i,j) returns 1, otherwise 0.
    auto isConnected{
        [&which_layer](int i, int j) {
            if (j < i)
                std::swap(i, j); // Make sure i is less than j
            if ((which_layer[j] - which_layer[i] == 1) && ((j == i + which_layer[i] + 1) || (j == i + which_layer[i] + 2)))
                return true;
            else
                return false;
        }};

    for (int j{0}; j < num_numbers; ++j)
    {
        std::vector<int> index_subvector{sorted_indices.begin(),sorted_indices.begin()+j};
        printPyramid(string_pyramid, index_subvector);
        std::cin.get();
    }

    // Turns out I will just highlight all the biggest numbers one by one and figure out a chain myself. For problem 67 will have to automate this.

    return 0;
}