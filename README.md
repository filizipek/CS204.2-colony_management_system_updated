# Updated Colony Management System

## Overview
This is an updated version of the Colony Management System designed by Filiz Ipek Oktay. This program allows users to manage resources, construct and destruct buildings in a colony, and view the colony's status. The system uses a doubly linked list (DLL) structure to represent the stock, consumption, and colony information.

## File Input
The program reads information from three files:
1. **Stock File**: Contains information about available resources and their quantities.
2. **Consumption File**: Specifies the resource consumption for each building type.
3. **Colony File**: Describes the current state of the colony, including building types and empty blocks.

## Program Functions

### 1. Construct a New Building
- Users can construct a new building in the colony.
- The program checks if the building type is valid and if there are sufficient resources in the stock.
- Users specify the building type and the index of the empty block where the building should be constructed.

### 2. Destruct/Disassemble a Building
- Users can destruct or disassemble a building from the colony.
- The program checks if the specified building type exists in the colony.
- Resources consumed during construction are loaded back to the stock.

### 3. Print the Colony
- Displays the current state of the colony.

### 4. Print the Colony in Reverse
- Displays the colony in reverse order.

### 5. Print the Colony with Inner Empty Blocks
- Displays the colony, showing inner empty blocks.

### 6. Print the Colony with Inner Empty Blocks in Reverse
- Displays the colony in reverse order, showing inner empty blocks.

### 7. Print the Stock
- Displays the current state of the stock.

### 8. Exit
- Exits the program, clearing memory and terminating execution.

## Implementation Details
- The system uses three DLLs: stockNode for stock information, consumpNode for consumption information, and colonyNode for colony information.
- Memory is dynamically allocated for nodes in each DLL.
- Functions are implemented to handle file input, validate building types, check stock sufficiency, and update resource quantities.
- The program includes an interactive menu for user input and navigation.

## Usage
1. Run the program.
2. Enter the names of the stock, consumption, and colony files when prompted.
3. Choose options from the menu to manage the colony.
4. Exit the program when done.

## Note
- Ensure that the input files are correctly formatted to prevent errors in the program execution.

**Developed by Filiz Ipek Oktay **
