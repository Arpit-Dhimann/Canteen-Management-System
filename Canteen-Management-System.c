// ============================================================
// Canteen Management System
// Author: Arpit Dhiman
// Description:
// A console-based application to manage canteen orders using
// queue data structures (circular queue for students and
// priority queue for staff).
// Features include order placement, serving, cancellation,
// and order history tracking.
// ============================================================

#include <stdio.h>
#include <string.h>
#define TOTAL_ITEMS   18   
#define MAX_STUDENT    5   
#define MAX_STAFF      3   
#define MAX_HISTORY   20   

struct MenuItem {
    int   id;
    char  name[50];
    float price;
    char  category[20];  
    char  type[10];      
};


struct Order {
    int   id;            
    char  name[50];     
    char  item[50];      
    int   quantity;      
    float totalPrice;    
    char  role[10];      
    char  status[15];    
};

struct MenuItem menu[TOTAL_ITEMS] = {
    // Breakfast
    {1,  "Poha",                        30.0,  "Breakfast",    "Veg"},
    {2,  "Idli Sambar (2 pcs)",         40.0,  "Breakfast",    "Veg"},
    {3,  "Bread Omelette",              35.0,  "Breakfast",    "Non-Veg"},
    {4,  "Upma",                        25.0,  "Breakfast",    "Veg"},
    // Main Course
    {5,  "Dal Rice",                    60.0,  "Main Course",  "Veg"},
    {6,  "Chicken Curry + Rice",        80.0,  "Main Course",  "Non-Veg"},
    {7,  "Paneer Butter Masala + Roti", 70.0,  "Main Course",  "Veg"},
    {8,  "Egg Fried Rice",              90.0,  "Main Course",  "Non-Veg"},
    {9,  "Veg Biryani",                 65.0,  "Main Course",  "Veg"},
    {10, "Chole Bhature",               55.0,  "Main Course",  "Veg"},
    // Snacks
    {11, "Samosa (2 pcs)",              20.0,  "Snacks",       "Veg"},
    {12, "Veg Puff",                    30.0,  "Snacks",       "Veg"},
    {13, "Chicken Roll",                40.0,  "Snacks",       "Non-Veg"},
    {14, "Aloo Tikki (2 pcs)",          25.0,  "Snacks",       "Veg"},
    // Beverages
    {15, "Tea",                         15.0,  "Beverages",    "Veg"},
    {16, "Coffee",                      20.0,  "Beverages",    "Veg"},
    {17, "Cold Drink (Bottle)",         25.0,  "Beverages",    "Veg"},
    {18, "Fresh Juice",                 30.0,  "Beverages",    "Veg"}
};

struct Order studentQueue[MAX_STUDENT];  
int s_front = -1;   
int s_rear  = -1;   

int isStudentFull() {
    return ((s_rear + 1) % MAX_STUDENT == s_front);
}

int isStudentEmpty() {
    return (s_front == -1);  
}

void enqueueStudent(struct Order newOrder) {
    if (isStudentFull()) {
        printf("\n  Queue is Full! Please wait for orders to be served.\n");
        return;
    }

    if (s_front == -1) {
        s_front = s_rear = 0;
    } else {
        s_rear = (s_rear + 1) % MAX_STUDENT;
    }

    studentQueue[s_rear] = newOrder;   
    printf("\n  Order placed! (Student Queue)\n");
}

struct Order dequeueStudent() {
    struct Order served = studentQueue[s_front];  

    if (s_front == s_rear) {
        s_front = s_rear = -1;
    } else {
        s_front = (s_front + 1) % MAX_STUDENT;
    }

    return served;
}

struct Order staffQueue[MAX_STAFF]; 
int f_front = -1;
int f_rear  = -1;

int isStaffFull() {
    return (f_rear == MAX_STAFF - 1); 
}

int isStaffEmpty() {
    return (f_front == -1);
}

void enqueueStaff(struct Order newOrder) {
    if (isStaffFull()) {
        printf("\n  Staff queue is full!\n");
        return;
    }

    if (f_front == -1) {
        f_front = f_rear = 0;
    } else {
        f_rear++;
    }

    staffQueue[f_rear] = newOrder;
    printf("\n  Order placed! (Staff Priority Queue)\n");
}

struct Order dequeueStaff() {
    struct Order served = staffQueue[f_front];

    if (f_front == f_rear) {
        f_front = f_rear = -1;  
    } else {
        f_front++; 
    }

    return served;
}

struct Order history[MAX_HISTORY];  
int historyCount = 0;               

void saveToHistory(struct Order o) {
    if (historyCount < MAX_HISTORY) {
        history[historyCount] = o;
        historyCount++;
    }
}

int orderIDCounter = 100; 

int getNewOrderID() {
    return orderIDCounter++; 
}

void displayCategory(char category[]) {
    printf("\n  %-4s %-32s %-12s %s\n", "No.", "Item Name", "Type", "Price");
    printf("  -------------------------------------------------------\n");

    int i;
    for (i = 0; i < TOTAL_ITEMS; i++) {
        if (strcmp(menu[i].category, category) == 0) {
            printf("  %-4d %-32s %-12s Rs.%.2f\n",
                menu[i].id,
                menu[i].name,
                menu[i].type,
                menu[i].price);
        }
    }
}

void displayMenu() {
    printf("\n");
    printf("  =======================================================\n");
    printf("                  WELCOME TO OUR CANTEEN                 \n");
    printf("  =======================================================\n");

    printf("\n  BREAKFAST");
    displayCategory("Breakfast");

    printf("\n\n  MAIN COURSE");
    displayCategory("Main Course");

    printf("\n\n  SNACKS");
    displayCategory("Snacks");

    printf("\n\n  BEVERAGES");
    displayCategory("Beverages");

    printf("\n  =======================================================\n");
    printf("               Total Items Available: %d\n", TOTAL_ITEMS);
    printf("  =======================================================\n");
}

void placeOrder() {
    struct Order newOrder;
    int itemChoice, roleChoice;

    displayMenu();

    printf("\n  Enter your name: ");
    scanf(" %[^\n]", newOrder.name); 

    printf("  Are you:\n");
    printf("  1. Student\n");
    printf("  2. Staff\n");
    printf("  Your choice: ");
    scanf("%d", &roleChoice);

    if (roleChoice == 1) {
        strcpy(newOrder.role, "Student");
    } else if (roleChoice == 2) {
        strcpy(newOrder.role, "Staff");
    } else {
        printf("  Invalid choice!\n");
        return;
    }

    printf("  Enter item number (1 to %d): ", TOTAL_ITEMS);
    scanf("%d", &itemChoice);

    if (itemChoice < 1 || itemChoice > TOTAL_ITEMS) {
        printf("  Invalid item number!\n");
        return;
    }
    strcpy(newOrder.item, menu[itemChoice - 1].name); 

    printf("  Enter quantity: ");
    scanf("%d", &newOrder.quantity);

    if (newOrder.quantity <= 0) {
        printf("  Quantity must be at least 1!\n");
        return;
    }
    newOrder.id         = getNewOrderID();
    newOrder.totalPrice = menu[itemChoice - 1].price * newOrder.quantity;
    strcpy(newOrder.status, "Pending");

    printf("\n  -------------------------------------------------------\n");
    printf("  ORDER SUMMARY\n");
    printf("  -------------------------------------------------------\n");
    printf("  Order ID  : #%d\n",     newOrder.id);
    printf("  Name      : %s\n",      newOrder.name);
    printf("  Role      : %s\n",      newOrder.role);
    printf("  Item      : %s\n",      newOrder.item);
    printf("  Quantity  : %d\n",      newOrder.quantity);
    printf("  Total     : Rs.%.2f\n", newOrder.totalPrice);
    printf("  -------------------------------------------------------\n");

    if (strcmp(newOrder.role, "Staff") == 0) {
        enqueueStaff(newOrder); 
    } else {
        enqueueStudent(newOrder); 
    }
}

void serveNextOrder() {
    struct Order served;

    if (!isStaffEmpty()) {
        served = dequeueStaff();
        printf("\n  [PRIORITY] Serving Staff Order...\n");
    } else if (!isStudentEmpty()) {
        served = dequeueStudent();
        printf("\n  Serving Student Order...\n");
    } else {
        printf("\n  No orders to serve right now.\n");
        return;
    }

    strcpy(served.status, "Served");
    saveToHistory(served);

    printf("  -------------------------------------------------------\n");
    printf("  Order ID  : #%d\n",     served.id);
    printf("  Name      : %s\n",      served.name);
    printf("  Role      : %s\n",      served.role);
    printf("  Item      : %s\n",      served.item);
    printf("  Quantity  : %d\n",      served.quantity);
    printf("  Total     : Rs.%.2f\n", served.totalPrice);
    printf("  Status    : SERVED\n");
    printf("  -------------------------------------------------------\n");
}

// ============================================================
//                DISPLAY PENDING ORDERS
// ============================================================

void displayOrders() {
    printf("\n  =======================================================\n");
    printf("                  ALL PENDING ORDERS                     \n");
    printf("  =======================================================\n");

    printf("\n  [STAFF QUEUE] (Priority)\n");
    if (isStaffEmpty()) {
        printf("  No staff orders pending.\n");
    } else {
        int i;
        for (i = f_front; i <= f_rear; i++) {
            printf("  #%d | %-15s | %-30s | Qty: %d | Rs.%.2f\n",
                staffQueue[i].id,
                staffQueue[i].name,
                staffQueue[i].item,
                staffQueue[i].quantity,
                staffQueue[i].totalPrice);
        }
    }

    printf("\n  [STUDENT QUEUE] (Circular)\n");
    if (isStudentEmpty()) {
        printf("  No student orders pending.\n");
    } else {
        int i = s_front; 
        while (1) {
            printf("  #%d | %-15s | %-30s | Qty: %d | Rs.%.2f\n",
                studentQueue[i].id,
                studentQueue[i].name,
                studentQueue[i].item,
                studentQueue[i].quantity,
                studentQueue[i].totalPrice);

            if (i == s_rear) break;           
            i = (i + 1) % MAX_STUDENT;    
        }
    }

    printf("\n  =======================================================\n");
}

void viewHistory() {
    printf("\n  =======================================================\n");
    printf("                    ORDER HISTORY                        \n");
    printf("  =======================================================\n");

    if (historyCount == 0) {
        printf("  No orders served yet.\n");
    } else {
        int i;
        for (i = 0; i < historyCount; i++) {
            printf("  #%d | %-15s | %-10s | %-30s | Qty: %d | Rs.%.2f | %s\n",
                history[i].id,
                history[i].name,
                history[i].role,
                history[i].item,
                history[i].quantity,
                history[i].totalPrice,
                history[i].status);
        }
    }

    printf("  =======================================================\n");
}

void cancelOrder() {
    int targetID, found = 0;

    printf("\n  Enter Order ID to cancel: #");
    scanf("%d", &targetID);

    for (int i = f_front; i <= f_rear; i++) {
        if (staffQueue[i].id == targetID) {
            for (int j = i; j < f_rear; j++) {
                staffQueue[j] = staffQueue[j + 1];
            }
            f_rear--;  
            if (f_rear < f_front) {
                f_front = f_rear = -1;
            }

            printf("  Order #%d cancelled (Staff Queue).\n", targetID);
            found = 1;
            break;
        }
    }

    if (!found && !isStudentEmpty()) {
        struct Order temp[MAX_STUDENT];
        int tempCount = 0;
        int k = s_front;

        while (1) {
            if (studentQueue[k].id == targetID) {
                found = 1;  
            } else {
                temp[tempCount] = studentQueue[k];
                tempCount++;
            }

            if (k == s_rear) break;
            k = (k + 1) % MAX_STUDENT;
        }

        if (found) {
            s_front = -1;
            s_rear  = -1;

            for (int j = 0; j < tempCount; j++) {
                if (s_front == -1) {
                    s_front = s_rear = 0;
                } else {
                    s_rear = (s_rear + 1) % MAX_STUDENT;
                }
                studentQueue[s_rear] = temp[j];
            }

            printf("  Order #%d cancelled (Student Queue).\n", targetID);
        }
    }

    if (!found) {
        printf("  Order #%d not found.\n", targetID);
    }
}

int main() {
    int choice;

    printf("\n  Welcome to the College Canteen Order System!\n");

    while (1) {
        printf("\n  =======================================================\n");
        printf("                       MAIN MENU                         \n");
        printf("  =======================================================\n");
        printf("  1. View Menu\n");
        printf("  2. Place Order\n");
        printf("  3. Serve Next Order\n");
        printf("  4. View Pending Orders\n");
        printf("  5. Cancel Order\n");
        printf("  6. View Order History\n");
        printf("  7. Exit\n");
        printf("  =======================================================\n");
        printf("  Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                placeOrder();
                break;
            case 3:
                serveNextOrder();
                break;
            case 4:
                displayOrders();
                break;
            case 5:
                cancelOrder();
                break;
            case 6:
                viewHistory();
                break;
            case 7:
                printf("\n  Thank you! Goodbye.\n\n");
                return 0;
            default:
                printf("  Invalid choice! Try again.\n");
        }
    }

    return 0;
}