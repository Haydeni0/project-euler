"""
The file, poker.txt, contains one-thousand random hands dealt to two players. Each line of the file contains ten cards (separated by a single space): 
the first five are Player 1's cards and the last five are Player 2's cards. 
You can assume that all hands are valid (no invalid characters or repeated cards), each player's hand is in no specific order, and in each hand there is a clear winner.
How many hands does Player 1 win?
"""
import numpy as np


class PokerHand:
    # A poker hand will consist of 5 cards, each with a suit and value.
    # Eg. ["8C", "TS", "KC", "9H", "4S"]

    # Static variables with hand hierarchy
    s_value_hierarchy = ["2", "3", "4", "5",
                         "6", "7", "8", "9", "T", "J", "Q", "K", "A"]
    s_handtype_hierarchy = ["HighCard", "OnePair", "TwoPairs", "ThreeOfAKind",
                            "Straight", "Flush", "FullHouse", "FourOfAKind", "StraightFlush"]

    def __init__(self, hand_list):
        # Make sure there are 5 cards in the hand
        assert len(hand_list) == 5
        # Instance variables
        self.m_suit = []
        self.m_value = []
        self.m_value_idx = []
        for card in hand_list:
            self.m_value.append(card[0])
            self.m_suit.append(card[1])
            self.m_value_idx.append(PokerHand.s_value_hierarchy.index(card[0]))
        # Sort the cards by value_idx

        # sort by the first list (m_value_idx)
        def sortkey(item): return item[0]
        zipped_values = zip(self.m_value_idx, self.m_value, self.m_suit)
        sorted_values = sorted(zipped_values, key=sortkey)
        tuples = zip(*sorted_values)
        self.m_value_idx, self.m_value, self.m_suit = [
            list(tuple) for tuple in tuples]
        # Get the hand type
        self.handtype = self.getHandtype()

    def getHandtype(self):
        # First determine if the hand is a flush
        is_flush = True
        for val in self.m_suit[1:]:
            if val != self.m_suit[0]:
                is_flush = False
                break
        # Next, determine if hand is a straight
        straight_list = np.arange(
            self.m_value_idx[0], self.m_value_idx[-1] + 1)
        if len(straight_list) == 5:
            if all(straight_list == np.array(self.m_value_idx)):
                is_straight = True
            else:
                is_straight = False
        else:
            is_straight = False

        if is_straight and is_flush:
            return "StraightFlush"

        elif is_straight:
            return "Straight"
        elif is_flush:
            return "Flush"

        # Find any pairs
        # Create two lists that show the unique value indices and how many times they occur
        # Eg. for value_idx = [4,5,5,6,6], the lists will be [4,5,6] and [1,2,2].
        self.unique_value_idx = list(set(self.m_value_idx))
        self.unique_value_idx_occurrence = list(
            self.m_value_idx.count(idx) for idx in self.unique_value_idx)

        # Sort these lists first by number of occurrences, and breaking ties with value_idx (for use in comparing hands later)
        def sortkey(item): return (item[1], item[0])
        unique_val_zip = zip(self.unique_value_idx,
                             self.unique_value_idx_occurrence)
        sorted_zip = sorted(unique_val_zip, key=sortkey)
        self.unique_value_idx, self.unique_value_idx_occurrence = [
            list(val) for val in zip(*sorted_zip)]

        if len(self.unique_value_idx) == 5:
            return "HighCard"
        elif len(self.unique_value_idx) == 4:
            return "OnePair"
        elif len(self.unique_value_idx) == 3:
            # Two pairs or three of a kind
            if 3 in self.unique_value_idx_occurrence:
                return "ThreeOfAKind"
            return "TwoPairs"
        elif len(self.unique_value_idx) == 2:
            # Full house or four of a kind
            if 4 in self.unique_value_idx_occurrence:
                return "FourOfAKind"
            return "FullHouse"
        else:
            raise Exception("Can't have a five pair")

    # For comparing hands:
    def handCompare(self, other):
        # Return 1 if self > other, return 0 if self == other, return -1 if self < other

        # First, compare handtype using s_handtype_hierarchy
        if PokerHand.s_handtype_hierarchy.index(self.handtype) > PokerHand.s_handtype_hierarchy.index(other.handtype):
            return 1
        elif PokerHand.s_handtype_hierarchy.index(self.handtype) < PokerHand.s_handtype_hierarchy.index(other.handtype):
            return -1

        # If the hand types are equal:
        for j in range(len(self.unique_value_idx) - 1, 0, -1):
            if self.unique_value_idx[j] == other.unique_value_idx[j]:
                continue
            elif self.unique_value_idx[j] < other.unique_value_idx[j]:
                return -1
            elif self.unique_value_idx[j] > other.unique_value_idx[j]:
                return 1
        else:
            return 0



    def __gt__(self, other):
        if self.handCompare(other) == 1:
            return True
        else:
            return False

    def __eq__(self, other):
        if self.handCompare(other) == 0:
            return True
        else:
            return False

    def __lt__(self, other):
        if self.handCompare(other) == -1:
            return True
        else:
            return False


# test_hand1 = ["4D", "6S", "9H", "QH", "QC"]
# test_hand2 = ["3D", "6D", "7H", "QD", "QS"]

filepath = "./Questions/Qs1-100/Q54/poker.txt"


Player1Wins = 0
with open(filepath, "r") as f:
    for line in f:
        print()
        print(line[:-1])
        hand1 = PokerHand(line[0:14].split(" "))
        hand2 = PokerHand(line[15:29].split(" "))
        print(hand1.m_value, hand2.m_value)
        print(hand1.m_suit, hand2.m_suit)
        print(hand1.handtype, hand2.handtype)
        if hand1 > hand2:
            Player1Wins += 1
            print("P1 Win")
        else:
            print("P1 Lose")


print(Player1Wins)
