#include <stdio.h>
#include <time.h>

struct Payment {
    int transactionID;
    int machineID;
    float amount;
    time_t timestamp;
};

struct Item {
    int productID;
    char productName[100];
    int quantity;
};

struct MachineInventory {
    int machineID;
    struct Item items[100]; // assuming a maximum of 100 items per machine
    int numItems;
};

struct CentralStock {
    int productID;
    char productName[100];
    int quantity;
};

//Payments - Everything
void addPayment(struct Payment payments[], int *numPayments) {
    struct Payment newPayment;
    
    printf("Enter transaction ID: ");
    scanf("%d", &newPayment.transactionID);
    
    printf("Enter machine ID: ");
    scanf("%d", &newPayment.machineID);
    
    printf("Enter amount: ");
    scanf("%f", &newPayment.amount);
    
    newPayment.timestamp = time(NULL);
    
    payments[*numPayments] = newPayment;
    (*numPayments)++;
    
    printf("Payment added successfully!\n");
}

void removePayment(struct Payment payments[], int *numPayments) {
    int transactionID;
    int i, found = 0;
    
    printf("Enter transaction ID to remove: ");
    scanf("%d", &transactionID);
    
    for (i = 0; i < *numPayments; i++) {
        if (payments[i].transactionID == transactionID) {
            found = 1;
            
            // Remove the payment by shifting the elements
            for (int j = i; j < *numPayments - 1; j++) {
                payments[j] = payments[j + 1];
            }
            
            (*numPayments)--;
            printf("Payment removed successfully!\n");
            break;
        }
    }
    
    if (!found) {
        printf("Payment not found.\n");
    }
}

void viewPayments(struct Payment payments[], int numPayments) {
    if (numPayments == 0) {
        printf("No payment details available.\n");
        return;
    }
    
    printf("Payment Details:\n");
    
    for (int i = 0; i < numPayments; i++) {
        printf("Transaction ID: %d\n", payments[i].transactionID);
        printf("Machine ID: %d\n", payments[i].machineID);
        printf("Amount: %.2f\n", payments[i].amount);
        printf("Timestamp: %s", ctime(&payments[i].timestamp));
        printf("--------------------\n");
    }
}

int PaymentsMain() {
    struct Payment payments[100]; // assuming a maximum of 100 payments
    int numPayments = 0;
    int choice;
    int done = 0; // flag to determine if the user is done
    
    printf("Welcome to the Vending Machine Management System!\n");
    
    while (!done) {
        // Display the options for the user
        printf("Please select an option:\n");
        printf("1. Add Payment\n");
        printf("2. Remove Payment\n");
        printf("3. View Payments\n");
        printf("4. Done (Exit)\n");
        printf("Enter your choice (1-4): ");
        
        // Read the user's choice
        scanf("%d", &choice);
        
        // Process the user's choice
        switch (choice) {
            case 1:
                // Add new payment details
                addPayment(payments, &numPayments);
                break;
            case 2:
                // Remove past payment details
                removePayment(payments, &numPayments);
                break;
            case 3:
                // View all payment details
                viewPayments(payments, numPayments);
                break;
            case 4:
                // User is done, exit the loop
                done = 1;
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    
    return 0;
}

//Machines - Everything
void addMachine(struct MachineInventory machines[], int *numMachines) {
    if (*numMachines >= 100) {
        printf("Maximum machine capacity reached. Cannot add more machines.\n");
        return;
    }
    
    int machineID;
    
    printf("Enter machine ID: ");
    scanf("%d", &machineID);
    
    for (int i = 0; i < *numMachines; i++) {
        if (machines[i].machineID == machineID) {
            printf("Machine with ID %d already exists.\n", machineID);
            return;
        }
    }
    
    struct MachineInventory newMachine;
    newMachine.machineID = machineID;
    newMachine.numItems = 0;
    
    machines[*numMachines] = newMachine;
    (*numMachines)++;
    
    printf("Machine with ID %d added successfully!\n", machineID);
}

void removeMachine(struct MachineInventory machines[], int *numMachines) {
    int machineID;
    
    printf("Enter machine ID to remove: ");
    scanf("%d", &machineID);
    
    int machineIndex = -1;
    
    for (int i = 0; i < *numMachines; i++) {
        if (machines[i].machineID == machineID) {
            machineIndex = i;
            break;
        }
    }
    
    if (machineIndex == -1) {
        printf("Machine not found.\n");
        return;
    }
    
    for (int i = machineIndex; i < *numMachines - 1; i++) {
        machines[i] = machines[i + 1];
    }
    
    (*numMachines)--;
    
    printf("Machine with ID %d removed successfully!\n", machineID);
}

void addItem(struct MachineInventory machines[], int machineIndex) {
    int productID;
    int quantityToAdd;
    
    printf("Enter product ID: ");
    scanf("%d", &productID);
    
    printf("Enter quantity to add: ");
    scanf("%d", &quantityToAdd);
    
    struct MachineInventory *machine = &machines[machineIndex];
    
    for (int i = 0; i < machine->numItems; i++) {
        if (machine->items[i].productID == productID) {
            machine->items[i].quantity += quantityToAdd;
            printf("Item quantity updated successfully!\n");
            return;
        }
    }
    
    if (machine->numItems >= 100) {
        printf("Maximum item capacity reached. Cannot add more items.\n");
        return;
    }
    
    struct Item newItem;
    newItem.productID = productID;
    newItem.quantity = quantityToAdd;
    
    printf("Enter product name: ");
    scanf("%s", newItem.productName);
    
    machine->items[machine->numItems] = newItem;
    machine->numItems++;
    
    printf("Item added successfully!\n");
}

void removeItem(struct MachineInventory machines[], int machineIndex) {
    int productID;
    int quantityToRemove;
    
    printf("Enter product ID to remove: ");
    scanf("%d", &productID);
    
    printf("Enter quantity to remove: ");
    scanf("%d", &quantityToRemove);
    
    struct MachineInventory *machine = &machines[machineIndex];
    
    for (int i = 0; i < machine->numItems; i++) {
        if (machine->items[i].productID == productID) {
            if (machine->items[i].quantity >= quantityToRemove) {
                machine->items[i].quantity -= quantityToRemove;
                
                if (machine->items[i].quantity == 0) {
                    for (int j = i; j < machine->numItems - 1; j++) {
                        machine->items[j] = machine->items[j + 1];
                    }
                    
                    machine->numItems--;
                }
                
                printf("Item removed successfully!\n");
            } else {
                printf("Insufficient quantity. Cannot remove item.\n");
            }
            
            return;
        }
    }
    
    printf("Item not found in the machine.\n");
}

void viewMachineInventory(struct MachineInventory machine) {
    printf("Machine ID: %d\n", machine.machineID);
    
    if (machine.numItems == 0) {
        printf("No items in inventory.\n");
        return;
    }
    
    printf("Inventory:\n");
    
    for (int i = 0; i < machine.numItems; i++) {
        printf("Product ID: %d\n", machine.items[i].productID);
        printf("Product Name: %s\n", machine.items[i].productName);
        printf("Quantity: %d\n", machine.items[i].quantity);
        printf("--------------------\n");
    }
}

void showNumMachines(int numMachines) {
    printf("Number of machines: %d\n", numMachines);
}

int MachinesMain() {
    struct MachineInventory machines[100]; // assuming a maximum of 100 machines
    int numMachines = 0;
    int choice;
    int done = 0;
    
    while (!done) {
        printf("\nMachine Inventory Management\n");
        printf("1. Add new machine\n");
        printf("2. Remove existing machine\n");
        printf("3. Show number of machines\n");
        printf("4. Update machine inventory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addMachine(machines, &numMachines);
                break;
            case 2:
                removeMachine(machines, &numMachines);
                break;
            case 3:
                showNumMachines(numMachines);
                break;
            case 4: {
                int machineID;
                
                printf("Enter machine ID: ");
                scanf("%d", &machineID);
                
                int machineIndex = -1;
                
                for (int i = 0; i < numMachines; i++) {
                    if (machines[i].machineID == machineID) {
                        machineIndex = i;
                        break;
                    }
                }
                
                if (machineIndex == -1) {
                    printf("Machine not found.\n");
                    break;
                }
                
                int updateChoice;
                int updateDone = 0;

                while (!updateDone){
                
                    printf("\nMachine Inventory Management - Machine %d\n", machineID);
                    printf("1. Add item\n");
                    printf("2. Remove item\n");
                    printf("3. View machine inventory\n");
                    printf("4. Done\n");
                    printf("Enter your choice: ");
                    scanf("%d", &updateChoice);
                    
                    switch (updateChoice) {
                        case 1:
                            addItem(machines, machineIndex);
                            break;
                        case 2:
                            removeItem(machines, machineIndex);
                            break;
                        case 3:
                            viewMachineInventory(machines[machineIndex]);
                            break;
                        case 4:
                            updateDone = 1;
                            printf("Exiting update mode for Machine %d...\n", machineID);
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                            break;
                    }
                }
                
                break;
            }
            case 5:
                done = 1;
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    
    return 0;
}

//Central Stock- everything
void addStock(struct CentralStock stock[], int *numStock) {
    struct CentralStock newStock;
    
    printf("Enter product ID: ");
    scanf("%d", &newStock.productID);
    
    printf("Enter product name: ");
    scanf("%s", newStock.productName);
    
    printf("Enter quantity: ");
    scanf("%d", &newStock.quantity);
    
    int i;
    for (i = 0; i < *numStock; i++) {
        if (stock[i].productID == newStock.productID) {
            stock[i].quantity += newStock.quantity;
            printf("Stock updated successfully!\n");
            return;
        }
    }
    
    stock[*numStock] = newStock;
    (*numStock)++;
    
    printf("Stock added successfully!\n");
}

void removeStock(struct CentralStock stock[], int *numStock) {
    int productID;
    int quantityToRemove;
    int i, found = 0;
    
    printf("Enter product ID to remove: ");
    scanf("%d", &productID);
    
    printf("Enter quantity to remove: ");
    scanf("%d", &quantityToRemove);
    
    for (i = 0; i < *numStock; i++) {
        if (stock[i].productID == productID) {
            found = 1;
            
            if (stock[i].quantity >= quantityToRemove) {
                stock[i].quantity -= quantityToRemove;
                
                if (stock[i].quantity == 0) {
                    // Remove the stock by shifting the elements
                    for (int j = i; j < *numStock - 1; j++) {
                        stock[j] = stock[j + 1];
                    }
                    
                    (*numStock)--;
                }
                
                printf("Stock removed successfully!\n");
            } else {
                printf("Insufficient quantity. Cannot remove stock.\n");
            }
            
            break;
        }
    }
    
    if (!found) {
        printf("Stock not found.\n");
    }
}

void viewStock(struct CentralStock stock[], int numStock) {
    if (numStock == 0) {
        printf("No stock details available.\n");
        return;
    }
    
    printf("Central Stock Details:\n");
    
    for (int i = 0; i < numStock; i++) {
        printf("Product ID: %d\n", stock[i].productID);
        printf("Product Name: %s\n", stock[i].productName);
        printf("Quantity: %d\n", stock[i].quantity);
        printf("--------------------\n");
    }
}

int CentralStockMain() {
    struct CentralStock stock[100]; // assuming a maximum of 100 stock items
    int numStock = 0;
    int choice;
    int done = 0; // flag to determine if the user is done
    
    printf("Welcome to the Central Stock Management System!\n");
    
    while (!done) {
        // Display the options for the user
        printf("Please select an option:\n");
        printf("1. Add Stock\n");
        printf("2. Remove Stock\n");
        printf("3. View Stock\n");
        printf("4. Done (Exit)\n");
        printf("Enter your choice (1-4): ");
        
        // Read the user's choice
        scanf("%d", &choice);
        
        // Process the user's choice
        switch (choice) {
            case 1:
                // Add new stock
                addStock(stock, &numStock);
                break;
            case 2:
                // Remove stock
                removeStock(stock, &numStock);
                break;
            case 3:
                // View stock
                viewStock(stock, numStock);
                break;
            case 4:
                // User is done, exit the loop
                done = 1;
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    
    return 0;
}



//Menu
int main() {
    int choice;
    int done = 0;
    
    printf("Welcome to the Vending Machine Management System!\n");
    
    while (!done) {
        // Display the options for the user
        printf("\nPlease select an option:\n");
        printf("1. Payments\n");
        printf("2. Vending Machines\n");
        printf("3. Central Stock\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        
        // Read the user's choice
        scanf("%d", &choice);
        
        // Process the user's choice
        switch (choice) {
            case 1:
                // Handle payments
                printf("You selected Payments.\n");
                PaymentsMain();
                // Implement the logic for payment management
                break;
            case 2:
                // Handle vending machines
                printf("You selected Vending Machines.\n");
                MachinesMain();
                // Implement the logic for vending machine management
                break;
            case 3:
                // Handle central stock
                printf("You selected Central Stock.\n");
                CentralStockMain();
                // Implement the logic for central stock management
                break;
            case 4:
                done = 1;
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    
    return 0;
}

