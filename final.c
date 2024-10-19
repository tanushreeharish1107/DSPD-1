#include <stdio.h>
#include <string.h>
#define MAX_TRANSACTIONS 500




struct Transaction {
    int transactionID;
    int buyerID;
    int sellerID;
    double energyAmount;  // in kWh
    double pricePerKwh;
    char timestamp[20];   // "YYYY-MM-DD-HH:MM"
} ;

struct Transaction transactions[MAX_TRANSACTIONS] = {
    {1, 101, 201, 500.0, 0.15, "2024-10-01 12:30"},
    {2, 102, 202, 600.0, 0.12, "2024-09-02 14:45"},
    {3, 103, 203, 750.0, 0.10, "2024-08-03 09:15"},
    {4, 104, 204, 800.0, 0.13, "2024-10-04 11:00"},
    {5, 101, 205, 550.0, 0.14, "2024-07-05 08:30"},
    {6, 102, 203, 450.0, 0.11, "2024-06-06 10:20"},
    {7, 105, 201, 900.0, 0.12, "2024-05-07 12:50"},
    {8, 106, 202, 350.0, 0.09, "2024-04-08 15:45"},
    {9, 107, 204, 700.0, 0.13, "2024-03-09 16:10"},
    {10, 101, 205, 680.0, 0.10, "2024-02-10 18:40"},
    {11, 102, 204, 600.0, 0.12, "2024-01-11 10:05"},
    {12, 103, 205, 740.0, 0.14, "2023-12-12 09:30"},
    {13, 106, 201, 500.0, 0.11, "2023-11-13 12:25"},
    {14, 107, 202, 300.0, 0.12, "2023-10-14 14:50"},
    {15, 108, 203, 850.0, 0.10, "2024-09-15 17:30"},
    {16, 109, 204, 900.0, 0.13, "2024-08-16 08:40"},
    {17, 110, 205, 450.0, 0.14, "2024-07-17 11:15"},
    {18, 101, 202, 800.0, 0.11, "2024-06-18 13:50"},
    {19, 102, 203, 650.0, 0.09, "2024-05-19 15:05"},
    {20, 103, 204, 780.0, 0.12, "2024-04-20 16:20"},
    {21, 104, 205, 550.0, 0.13, "2024-03-21 14:25"},
    {22, 106, 201, 600.0, 0.12, "2024-02-22 13:00"},
    {23, 107, 202, 550.0, 0.11, "2024-01-23 10:10"},
    {24, 108, 203, 750.0, 0.09, "2023-12-24 09:45"},
    {25, 109, 204, 600.0, 0.14, "2023-11-25 11:30"}
};

int transactionCount = 25;





struct Buyer
{
    int buyerID;
    double TotalenergyAmount;
    
};

struct Buyer buyers[MAX_TRANSACTIONS];
int buyerCount=0;

struct Seller
{
    int sellerID;
    double totalRevenue;
};

struct Seller sellers[MAX_TRANSACTIONS];
int sellerCount = 0;

struct BuyerSellerPair
{
    int buyerID;
    int sellerID;
    double totalEnergy;
    double totalRevenue;
    int BSCount;
};

struct BuyerSellerPair pairs[MAX_TRANSACTIONS];
int pairCount=0;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Function to insert or update a transaction
void Insert_Update(int TID, int BID, int SID, double energy, double price, const char* timeStamp) {
    int i = 0, found = 0;

    // Check if the transaction with the same TID already exists
    while (i < transactionCount && !found) {
        if (transactions[i].transactionID == TID) {
            found = 1;
           
           
        } else {
            i++;
        }
    }

    // If the transaction doesn't exist and space is available, add a new transaction
    if (!found) {
        if (transactionCount < MAX_TRANSACTIONS) {
            transactions[transactionCount].transactionID = TID;
            transactions[transactionCount].buyerID = BID;
            transactions[transactionCount].sellerID = SID;
            transactions[transactionCount].energyAmount = energy;
            transactions[transactionCount].pricePerKwh = price;
            strcpy(transactions[transactionCount].timestamp, timeStamp);

           

            transactionCount++;
            printf("--- Transaction Added Successfully ---\n");
        } 
    }
    else {
            printf("--- Transaction Entry Failed: Maximum transaction limit reached ---\n");
            if (found==1) printf("--- Transaction Already Exists ---\n");
        }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Function to display all transactions
void displayTransactions() {
    if (transactionCount == 0) {
        printf("\nNo transactions to display.\n");
        return;
    }

    printf("\nAll Transactions:\n");
    for (int i = 0; i < transactionCount; i++) {
        printf("Transaction ID: %d | Buyer ID: %d | Seller ID: %d | Energy: %.2lf kWh | Price: %.2lf per kWh | Timestamp: %s\n",
               transactions[i].transactionID, transactions[i].buyerID, transactions[i].sellerID,
               transactions[i].energyAmount, transactions[i].pricePerKwh, transactions[i].timestamp);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Function to display all transactions for a given seller ID
void DisplaySellerList(int ID){

     int found = 0;  // Flag to check if any transactions are found

    printf("Transactions for Seller ID: %d\n", ID);

    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].sellerID == ID) {
            printf("Transaction ID: %d | Buyer ID: %d | Energy: %.2lf kWh | Price per kWh: %.2lf | Timestamp: %s\n",
                   transactions[i].transactionID,
                   transactions[i].buyerID,
                   transactions[i].energyAmount,
                   transactions[i].pricePerKwh,
                   transactions[i].timestamp);
            found = 1;
        }
    }

    if (!found) {
        printf("No transactions found for Seller ID: %d\n",ID);
    }
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Function to display all transactions for a given buyer ID

void DisplayBuyerList(int ID){

    int found = 0;  // Flag to check if any transactions are found

    printf("Transactions for Buyer ID: %d\n", ID);
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].buyerID == ID) {
            printf("Transaction ID: %d | Seller ID: %d | Energy: %.2lf kWh | Price per kWh: %.2lf | Timestamp: %s\n",
                   transactions[i].transactionID,
                   transactions[i].sellerID,
                   transactions[i].energyAmount,
                   transactions[i].pricePerKwh,
                   transactions[i].timestamp);
            found = 1;
        }
    }

    if (!found) {
        printf("No transactions found for Buyer ID: %d\n",ID);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
//To get transactions within a given time period

int isWithinPeriod(const char* timestamp, const char* start, const char* end) {
    return strcmp(timestamp, start) >= 0 && strcmp(timestamp, end) <= 0;
}

void listTransactionsInPeriod(const char* start, const char* end) {
    int found = 0;
    printf("Transactions between %s and %s:\n", start, end);
    for (int i = 0; i < transactionCount; i++) {
        if (isWithinPeriod(transactions[i].timestamp, start, end)) {
            found = 1;
            printf("Transaction ID: %d, Buyer ID: %d, Seller ID: %d, Energy: %.2f kWh, Price: $%.2f/kWh, Timestamp: %s\n",
                   transactions[i].transactionID, transactions[i].buyerID,
                   transactions[i].sellerID, transactions[i].energyAmount,
                   transactions[i].pricePerKwh, transactions[i].timestamp);
        }
    }
    if (!found) {
        printf("No transactions found in the specified period.\n");
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//To find month with maximum month of transactions


void getMonthFromTimestamp(const char* timestamp, char* month) {
    strncpy(month, timestamp+5, 2);  // Extract the month characters (MM)
    month[2] = '\0';  // Ensure the string is null-terminated
}

void findMaxMonth(){
    int monthArr[12]={0};
    char month[2];
    
    for(int i=0;i<transactionCount;i++){
        getMonthFromTimestamp(transactions[i].timestamp,month);

        int monthNum= (month[0]-'0')*10 +(month[1]-'0')-1; //extracting month number from the string

        if(monthNum>0 && monthNum<12){
            monthArr[monthNum]++;
        }
    }

    //finding max month

    int maxTransactions=0;
    int maxMonthindex=-1;
    for(int i=0;i<12;i++){
        if(monthArr[i]>maxTransactions){
            maxTransactions=monthArr[i];
            maxMonthindex=i;

        }
    }

    if(maxMonthindex !=-1){
        printf("Month with maximum transactions : %d with %d transactions\n", maxMonthindex+1,maxTransactions);
    }
    else{
        printf("No transaction found\n");
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Function to calculoate total revenue by seller 

void TotalRevenueBySeller(int sid){
    float total_rev=0.0;
    for(int i=0;i<transactionCount;i++){
        if(transactions[i].sellerID ==sid){
             float RevenueAdd = transactions[i].energyAmount * transactions[i].pricePerKwh;

            total_rev+= RevenueAdd;

        }
    }

    if (total_rev > 0) {
        printf("Total Revenue for Seller %d: Rs. %.2f\n", sid, total_rev);
    } else {
        printf("No transactions found for Seller %d.\n", sid);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Sorting :
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//First updating the buyer structure. 

// Function to find a buyer by ID and return their index, or -1 if not found
int findBuyerIndex(int buyerID) {
    for (int i = 0; i < buyerCount; i++) {
        if (buyers[i].buyerID == buyerID) {
            return i;
        }
    }
    return -1; // Buyer not found
}



// Function to update energy bought by buyers
void updateEnergyBought() {
    for (int i = 0; i < MAX_TRANSACTIONS; i++) {
        int buyerIndex = findBuyerIndex(transactions[i].buyerID);
        if (buyerIndex == -1) {
            // If buyer not found, add a new buyer
            buyers[buyerCount].buyerID = transactions[i].buyerID;
            buyers[buyerCount].TotalenergyAmount = transactions[i].energyAmount;
            buyerCount++;
        } else {
            // If buyer found, update energy
            buyers[buyerIndex].TotalenergyAmount += transactions[i].energyAmount;
        }
    }
}

// Sorting Buyers by energy using Quick Sort;Using partition function to find swapping pivot
int partitionBuyers(struct Buyer buyers[], int low, int high) {
    double pivot = buyers[high].TotalenergyAmount;  // Pivot element (last element)
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j < high; j++) {
        if (buyers[j].TotalenergyAmount <= pivot) {
            i++; 

            struct Buyer temp=buyers[j];
            buyers[j]=buyers[i];
            buyers[i]=temp; 
            
        }
    }
    // Swap the pivot element with the element at index (i+1)

    struct Buyer temp=buyers[i+1];
            buyers[i+1]=buyers[high];
            buyers[high]=temp; 
    
    return (i + 1);
}

void quickSortBuyers(struct Buyer buyers[], int low, int high) {
    if (low<high) {
        // Partition 
        int pi = partitionBuyers(buyers,low,high);
        //using quicksort again recursively
        quickSortBuyers(buyers, low, pi - 1);
        quickSortBuyers(buyers, pi + 1, high);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//By Seller 

// Function to find a seller by ID and return their index, or -1 if not found
int findSellerIndex(int sellerID) {
    for (int i = 0; i < sellerCount; i++) {
        if (sellers[i].sellerID == sellerID) {
            return i;
        }
    }
    return -1; // Seller not found
}

// Function to update revenue for sellers
void updateRevenue() {
    for (int i = 0; i < MAX_TRANSACTIONS; i++) {
        int sellerIndex = findSellerIndex(transactions[i].sellerID);
        if (sellerIndex == -1) {
          
            // If seller not found, add a new seller
            sellers[sellerCount].sellerID = transactions[i].sellerID;
            sellers[sellerCount].totalRevenue = transactions[i].energyAmount * transactions[i].pricePerKwh;
            sellerCount++;
            
        } else {
            // If seller found, update revenue
            sellers[sellerIndex].totalRevenue += transactions[i].energyAmount * transactions[i].pricePerKwh;
        }
    }

   
}



// Partition function for Quick Sort, used to rearrange the array for quicksort
int partitionSeller(struct Seller sellers[], int low, int high) {
    double pivot = sellers[high].totalRevenue;  // Pivot element (last element)
    int i = (low - 1);  // Index of smaller element

    // Traverse the array and reorder elements based on pivot value
    for (int j = low; j < high; j++) {
       
        if (sellers[j].totalRevenue >= pivot) { 
            i++;  

            // Swap the current element with the element at index i
            struct Seller temp = sellers[j];
            sellers[j] = sellers[i];
            sellers[i] = temp;
        }
    }

    // Swap the pivot element with the element at index i+1
    struct Seller temp = sellers[i + 1];
    sellers[i + 1] = sellers[high];
    sellers[high] = temp;

    return (i + 1);  // Return pivot index
}

// Quick Sort function to recursively sort the sellers array
void quickSortSellers(struct Seller sellers[], int low, int high) {
    if (low < high) {
        // Partition the array and get the pivot index
        int pi = partitionSeller(sellers, low, high);

        // Recursively sort the elements before and after the pivot
        quickSortSellers(sellers, low, pi - 1);
        quickSortSellers(sellers, pi + 1, high);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Function to find the Highest energy transaction

void findHighestEnergyTransaction() {
    if (transactionCount == 0) {
        printf("No transactions available.\n");
        return;
    }

    int maxIndex = 0;  // Index of the transaction with the highest energy amount

    // Iterate through the transactions to find the one with the maximum energy amount
    for (int i = 1; i < transactionCount; i++) {
        if (transactions[i].energyAmount > transactions[maxIndex].energyAmount) {
            maxIndex = i;
        }
    }

    // Display the transaction with the highest energy amount
    printf("Transaction with the Highest Energy Amount:\n");
    printf("Transaction ID: %d | Buyer ID: %d | Seller ID: %d | Energy: %.2lf kWh | Price: %.2lf per kWh | Timestamp: %s\n",
           transactions[maxIndex].transactionID, transactions[maxIndex].buyerID,
           transactions[maxIndex].sellerID, transactions[maxIndex].energyAmount,
           transactions[maxIndex].pricePerKwh, transactions[maxIndex].timestamp);


}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Functions for buyer and seller pairs :


void generateBuyerSellerPairs() {
    pairCount = 0;  // Reset the pair count

    // Loop through all transactions to populate buyer-seller pairs
    for (int i = 0; i < transactionCount; i++) {
        int buyerID = transactions[i].buyerID;
        int sellerID = transactions[i].sellerID;
        double energy = transactions[i].energyAmount;
        double price = transactions[i].pricePerKwh;
        
        int found = 0;

        // Check if this buyer-seller pair already exists in pairs[]
        for (int j = 0; j < pairCount; j++) {
            if (pairs[j].buyerID == buyerID && pairs[j].sellerID == sellerID) {
                // Pair exists, update the details
                pairs[j].BSCount++;  // Increment the transaction count
                pairs[j].totalEnergy += energy;  // Add energy
                pairs[j].totalRevenue += (energy * price);  // Add revenue
                found = 1;
                break;
            }
        }

        // If pair does not exist, add it
        if (!found && pairCount < MAX_TRANSACTIONS) {
            pairs[pairCount].buyerID = buyerID;
            pairs[pairCount].sellerID = sellerID;
            pairs[pairCount].totalEnergy = energy;
            pairs[pairCount].totalRevenue = energy * price;
            pairs[pairCount].BSCount = 1;  // Initialize transaction count to 1
            pairCount++;
        }
    }

    
}

//Function for maximum number of transactions pair 

void MaxTransactionPair(){
    int max_count=0;
    
    int BID;
    int SID;

    for(int i=0;i<pairCount;i++){
        if(pairs[i].BSCount>max_count){
            max_count=pairs[i].BSCount;
            
            BID=pairs[i].buyerID;
            SID=pairs[i].sellerID;
        }
    }

    printf("The pair %d - %d has maximum number transactions \n",BID,SID);
    printf("The number of transactions is %d\n",max_count);
}



void SortTransactions(){
    int i, j;
    int swapped;

    for (i = 0; i < pairCount && (swapped); i++) {
        swapped = 0;  

        // Perform a single pass of Bubble Sort
        for (j = 0; j < pairCount - i - 1; j++) {
            if (pairs[j].BSCount < pairs[j + 1].BSCount) {
                // Swap if the current pair has less number of transactions than the next one
                struct BuyerSellerPair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;

                swapped = 1;  
            }
        }

        // If no elements were swapped during this pass, the array is already sorted
       
    }
}


void SortRevenuePair(){
     int i, j;
    int swapped;

    for (i = 0; i < pairCount && (swapped); i++) {
        swapped = 0;  

        // Perform a single pass of Bubble Sort
        for (j = 0; j < pairCount - i - 1; j++) {
            if (pairs[j].totalRevenue < pairs[j + 1].totalRevenue) {
                // Swap if the current pair has less revenue than the next one
                struct BuyerSellerPair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;

                swapped = 1;  
            }
        }

        // If no elements were swapped during this pass, the array is already sorted
       
    }

}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Functions to display buyer and seller structures .

void displayBuyers(struct Buyer buyers[], int buyerCount) {
    for (int i = 0; i < buyerCount; i++) {
        printf("Buyer ID: %d | Energy Bought: %.2f kWh\n", buyers[i].buyerID, buyers[i].TotalenergyAmount);
    }
}

void displaySellers(struct Seller sellers[], int sellerCount) {
    for (int i = 0; i < sellerCount; i++) {
        printf("Seller ID: %d | Revenue Generated: %.2f\n", sellers[i].sellerID, sellers[i].totalRevenue);
    }
}

void displayPair(struct BuyerSellerPair pairs[], int pairCount  ){
    for (int i = 0; i < sellerCount; i++) {
        printf("Seller ID: %d | Buyer ID: %d | Number of Transactions : %d \n", pairs->sellerID, pairs->buyerID, pairs->BSCount);
    }
}


//---------------------------------------------------------------------------------------------------------------------------------------------
// Function to display the menu
void displayMenu() {
    printf("\nEnergy Trading Record Management System\n");
    printf("1. Add New Transaction\n");
    printf("2. Display All Transactions\n");
    printf("3.Display List of Transactions by Seller");
    printf("4.Display List of Transactions by Buyer");
    printf("5.List all transactions that took place in a specific time period.");
    printf("6.Display Month in which maximum transactions took place");
    printf("7. Calculate Total Revenue by Seller\n");
    printf("8.Sort the list of sellers based on their revenue generated.\n");
    printf("9.Display the Transaction with the Highest Energy Amount\n");
    printf("10.Sort the list of Buyers in order of Energy Bought\n");
    printf("11.Find out a pair of seller/buyer involved in maximum number of transactions. \n");
    printf("12.Sort all seller/buyer pairs in decreasing order of the number of transactions between them.\n");
    printf("13.Sort all seller/buyer pairs in decreasing order of the total revenue exchanged between them.\n");
    printf("14. Exit\n");
}


int main(){
    int choice;
    int flag = 1;

    displayMenu();

    while(flag){
       
        printf("Enter your choice: ");
        scanf("%d", &choice);
         int TID, BID, SID;
        double energy, price;
        char timestamp[20],start[20],end[20];

        switch (choice) {
            case 1:
            //add new transaction
                printf("Enter Transaction ID: ");
                scanf("%d", &TID);
                printf("Enter Buyer ID: ");
                scanf("%d", &BID);
                printf("Enter Seller ID: ");
                scanf("%d", &SID);
                printf("Enter Energy Amount (kWh): ");
                scanf("%lf", &energy);
                printf("Enter Price per kWh: ");
                scanf("%lf", &price);
                printf("Enter Timestamp (YYYY-MM-DD-HH:MM): ");
                scanf("%s", timestamp);
                Insert_Update(TID,BID,SID,energy,price,timestamp);
                break;
             case 2:
                // Display All Transactions
                displayTransactions();
                break;
            case 3:
                // Display All Transactions by seller 
                printf("Enter Seller ID: \n");
                scanf("%d",&SID);
                DisplaySellerList(SID);
                break;
            case 4:
                // Display All Transactions by buyer 
                printf("Enter Buyer ID: \n");
                scanf("%d",&BID);
                DisplayBuyerList(BID);
                break;    
            case 5:
                //List all transactions that took place in a specific time period.

                printf("Enter the Start (YYYY-MM-DD HH:MM): ");
                scanf("%s", start);
                printf("Enter the End (YYYY-MM-DD HH:MM): ");
                scanf("%s", end);
                listTransactionsInPeriod(start, end);
                break;

            case 6:
                //month with max transactions
                 findMaxMonth();
                 break;

            case 7:
                //total revenue by seller 
                printf("Enter Seller ID: ");
                scanf("%d", &SID);
                TotalRevenueBySeller(SID);
                break;
            case 8:
            //sort sellers by revenue 
                updateRevenue();
                quickSortSellers(sellers,0,sellerCount);
                displaySellers(sellers,sellerCount);
                break;

            case 9:
                findHighestEnergyTransaction();
                break;

            case 10:
            //sort buyers by energy
                updateEnergyBought();
                quickSortBuyers(buyers,0,buyerCount);
                displayBuyers(buyers,buyerCount);
                break;
            

            case 11:
            //find pair with max transactions
                generateBuyerSellerPairs();
                MaxTransactionPair();
                break;
            case 12:
            //sort pairs by number of transactions
                generateBuyerSellerPairs();
                SortTransactions();
                displayPair(pairs,pairCount);

            case 13:
            //sort pairs by revenue 
                generateBuyerSellerPairs();
                SortRevenuePair();
                displayPair(pairs,pairCount);

                
            case 14:
                flag=0;
                printf("Exiting program.\n");
               
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
    }





