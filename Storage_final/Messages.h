#pragma once
#include <iostream>
using namespace std;

const string INTRODUCTION = "Enter the operation you want to perform.";
const string FILE_OPTIONS = "The options regarding working with files are: open, close, save, saveas, help and exit.";
const string STORAGE_OPTIONS = "Storage options: add, remove, log, clean, losses.";
const string ENTER_COMMAND = "Command: ";
const string INVALID_PATH = "You have entered an invalid path! Forbidden characters are: / < | >";
const string INVALID_DAY = "You have entered an invalid day. Please try again!";
const string INVALID_MONTH = "You have entered an invalid month. Please try again!";
const string INVALID_YEAR = "You have entered an invalid year. It should be in the area between 1900 and 2100.";
const string LEAP_YEAR_FEBRUARY = "Wrong year or wrong number of days! In the leap years alone, February has 29 days.";
const string WRONG_NUMBER_DAYS = "Wrong number of days for this month! Please try again!";
const string ENTER_NAME = "Name: ";
const string NOT_ENTERED_NAME = "You have not entered a name!";
const string NOT_ENTERED_DATE = "You have not entered a date!";
const string INCORRECTLY_DATE = "This date was entered incorrectly! Follow this example: yyyy-mm-dd";
const string ENTER_QUANTITY = "Quantity: ";
const string QUANTITY_MUST_POSITIVE = "The quantity must be a positive number.";
const string THIRD_DECIMAL_PLACES = "The program works with numbers limited to the third decimal places!";
const string INVALID_NUMBER_ENTRY = "You have entered an invalid number entry!";
const string EXCESSIVE_NUMBER = "You have entered an excessive number! The allowed number of characters is: ";
const string NOT_ENTERED_QUANTITY = "You have not entered a quantity!";
const string ENTER_ANSWER = "Answer: ";
const string ALLOWED_ANSWERS = "Allowed answers are Yes or No.";
const string NOT_ENTERED_ANSWER = "You have not entered a answer!";
const string ENTER_EXPIRY_DATE = "Expiry Date: ";
const string DATE_EXPIRIES_TODAY = "This expiry date expires today. Are you sure you want to enter it ?";
const string WRONG_DATE = "In that case, it would be better to enter a new date!";
const string DATE_ALREADY_EXPIRED = "This expiry date has already expired! Please check the date again.";
const string ENTER_MANUFACTURERS_NAME = "Manufacturer's Name: ";
const string NOT_ENTERED_MANUFACTURERS_NAME = "You have not entered a manufacturer's name: !";
const string ENTER_UNIT_OF_MEASURE = "Unit of Measure: ";
const string ALLOWED_UNITS_OF_MEASURE = "The allowed units of measure are kg and l!";
const string NOT_ENTERED_UNITS_OF_MEASURE = "You have not entered a unit of measure!";
const string ENTER_COMMENT = "Comment: ";
const string IF_NOT_ENTERED_COMMENT = "no comment";
const string DEFAULT_VALUE = "default";
const string PRODUCT_CANNOT_BE_ADDED = "The product cannot be added because its quantity exceeds the maximum allowed for this product! You can only add: ";
const string SUCCESSFULLY_ADDED = "The product has been successfully added to the storage!";
const string NO_SUITABLE_PLACE = "There are already enough different types of products. No suitable place can be found for your product.";
const string VERY_CHAOTIC = "As much of this product as possible has been added to the storage, but for the rest, the arrangement will become very chaotic!";
const string ENOUGH_PRODUCT = "Unfortunately, this product cannot be added to the storage. There is enough of it.";
const string PRODUCTS_REMOVED_SUCCESSFULLY = "The products have been removed successfully!";
const string PRODUCT_REMOVED_SUCCESSFULLY = "The product has been removed successfully!";
const string PRODUCT_CANNOT_BE_REMOVED = "The product cannot be removed because the quantity you entered exceeds available in the storage. You can only remove: ";
const string DO_YOU_WANT_TO_REMOVE = "Do you want to remove the quantity that is available in the storage from this product ?";
const string SUCCESSFULLY_REARRANGEMENT = "Successful rearrangement completed!";
const string PRODUCT_NAME_NOT_FOUND = "Product name not found! Make sure you enter the name correctly.";
const string POSITION = "Position: ";
const string POSITIONS = "Positions: ";
const string NO_DATA_INSERTED = "There is still no data inserted!";
const string DATES_RECEIVE_INFORMATION = "Enter the start and end dates of the period from which you want to receive information!";
const string FROM = "From: ";
const string TO = "To: ";
const string NO_ACTIONS = "No actions have been taken during this period!";
const string PRICE_PER_UNIT_OF_MEASURE = "Price(BGN) per 1kg(l): ";
const string PRICE_MUST_POSITIVE = "The price must be a positive number.";
const string PRICES_LIMITED_SECOND_DECIMAL_PLACES = "The program works with prices limited to the second decimal places!";
const string NOT_ENTERED_PRICE = "You have not entered a price!";
const string DATES_RECEIVE_INFORMATION_LOSSES = "Enter the start and end dates of the period from which you want to receive information about the losses!";
const string NO_LOSSES = "No losses were incurred during this period!";
const string SUCCESSFULLY_CLEANING_REARRANGING = "Successful cleaning and rearranging!";
const string NO_PRODUCTS_NEED_CLEAN = "There are still no products that need to be cleaned from the storage.";
const string DO_YOU_WANT_KEEP_CHANGES = "Do you want to keep the changes made in storage ?";
const string FILE_EXISTS_SAME_NAME = "There is already a file with that name!";
const string NO_LOADED_PRODUCTS = "There are no loaded products in the storage yet!";
const string FORGOT_ENTER_PATH = "You forgot to enter a path!";
const string FIRST_OPEN_STORAGE = "To execute this command, you must first open the file!";
const string COMMAND_NOT_RECOGNIZED = "This command is not recognized, please make sure you have entered the command correctly!";
const string NOT_ENTERED_COMMAND = "You have not entered a command!";