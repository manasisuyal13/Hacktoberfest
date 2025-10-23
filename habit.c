/*
===========================================================
🧠 PROJECT: Smart Daily Habit Tracker (Console Version)
AUTHOR: Manasi Suyal
LANGUAGE: C
===========================================================
📘 ABOUT THIS CODE:
This program helps users track daily habits and store them 
in a file ("habits.txt"). Users can:
  ✅ Add new habits
  ✅ View all habits
  ✅ Mark habits as completed
  ✅ Save data between runs (persistent storage)

It demonstrates:
  - File handling
  - Struct usage
  - String operations
  - Menu-driven programming

Perfect for Hacktoberfest: small, practical, and unique!
===========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HABITS 50
#define MAX_NAME 50
#define FILENAME "habits.txt"

typedef struct {
    char name[MAX_NAME];
    int completed;  // 0 = not done, 1 = done
} Habit;

Habit habits[MAX_HABITS];
int habitCount = 0;

// Function prototypes
void loadHabits();
void saveHabits();
void addHabit();
void viewHabits();
void markHabitCompleted();
void clearScreen();

int main() {
    int choice;
    loadHabits();

    do {
        clearScreen();
        printf("=============================================\n");
        printf("         🌱 SMART DAILY HABIT TRACKER        \n");
        printf("=============================================\n");
        printf("1️⃣  Add New Habit\n");
        printf("2️⃣  View All Habits\n");
        printf("3️⃣  Mark Habit as Completed\n");
        printf("4️⃣  Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume newline

        switch(choice) {
            case 1: addHabit(); break;
            case 2: viewHabits(); break;
            case 3: markHabitCompleted(); break;
            case 4: 
                printf("\n💾 Saving progress... Goodbye!\n");
                saveHabits();
                exit(0);
            default: 
                printf("\n❌ Invalid choice! Please try again.\n");
        }
        printf("\nPress Enter to continue...");
        getchar();

    } while(1);

    return 0;
}

// Load existing habits from file
void loadHabits() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) return;

    while (fscanf(file, "%49[^,],%d\n", habits[habitCount].name, &habits[habitCount].completed) == 2) {
        habitCount++;
    }
    fclose(file);
}

// Save habits to file
void saveHabits() {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("❌ Error saving data.\n");
        return;
    }
    for (int i = 0; i < habitCount; i++) {
        fprintf(file, "%s,%d\n", habits[i].name, habits[i].completed);
    }
    fclose(file);
}

// Add a new habit
void addHabit() {
    if (habitCount >= MAX_HABITS) {
        printf("\n⚠️ You’ve reached the maximum habit limit!\n");
        return;
    }
    printf("\nEnter habit name: ");
    fgets(habits[habitCount].name, MAX_NAME, stdin);
    habits[habitCount].name[strcspn(habits[habitCount].name, "\n")] = 0;  // remove newline
    habits[habitCount].completed = 0;
    habitCount++;

    saveHabits();
    printf("✅ Habit added successfully!\n");
}

// View all habits
void viewHabits() {
    printf("\nYour Habits:\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < habitCount; i++) {
        printf("%d. %-30s [%s]\n", i + 1, habits[i].name, habits[i].completed ? "✅ Done" : "❌ Not Done");
    }
    if (habitCount == 0)
        printf("No habits added yet.\n");
}

// Mark a habit as completed
void markHabitCompleted() {
    viewHabits();
    if (habitCount == 0) return;

    int index;
    printf("\nEnter habit number to mark as completed: ");
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > habitCount) {
        printf("❌ Invalid number!\n");
        return;
    }
    habits[index - 1].completed = 1;
    saveHabits();
    printf("🎉 Great job! Habit marked as completed.\n");
}

// Clear console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
