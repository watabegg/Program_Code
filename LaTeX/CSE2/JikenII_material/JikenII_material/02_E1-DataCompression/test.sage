"""
Created on Fri Dec 14 10:01:26 2018

@author: hernan
"""
#Huffman coding and decoding

# sage.coding.source_coding.huffman.Huffman(source)
# It can build a Huffman code from a given string, or from the information of a dictionary associating to each key 
# (the elements of the alphabet) a weight (most of the time, a probability value or a number of occurrences).

# source can be either
# A string from which the Huffman encoding should be created.
# A dictionary that associates to each symbol of an alphabet a numeric value.
#   If we consider the frequency of each alphabetic symbol, then source is considered as the frequency table of 
#   the alphabet with each numeric (non-negative integer) value being the number of occurrences of a symbol.
#   The numeric values can also represent weights of the symbols. 
#   In that case, the numeric values are not necessarily integers, but can be real numbers.

# To construct a Huffman code for an alphabet, we use one of the following methods:
# 1. Let source be a string of symbols over an alphabet and feed source to the constructor of this class. 
#    Based on the input string, a frequency table is constructed that contains the frequency of each unique symbol in source. 
#    The alphabet in question is then all the unique symbols in source. 
#    A significant implication of this is that any subsequent string that we want to encode 
#    must contain only symbols that can be found in source.   
from sage.coding.source_coding.huffman import Huffman, frequency_table

message = "There once was a french fry"
print message
h1 = Huffman(message)
for letter, code in h1.encoding_table().items():
    print("'{}' : {}".format(letter, code))
    
# 2. Let source be the frequency table of an alphabet. 
#    We can feed this table to the constructor of this class. 
#    The table source can be a table of frequencies or a table of weights.
ft = frequency_table(message)
ft
h2 = Huffman(ft)


encoded = h1.encode(message)
print encoded

decoded = h1.decode(encoded)
print decoded

