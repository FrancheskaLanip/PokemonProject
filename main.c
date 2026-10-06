#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
#define MAX_POKEMON 100
#define MAX_TEAM 6

struct Pokemon {
    int id;
    char name[30];
    char type[20];
    int hp;
    int attack;
    int defense;
    char description[100];
};

// Global variables
struct Pokemon pokemons[MAX_POKEMON];
int totalPokemons = 0;
struct Pokemon team[MAX_TEAM];
int teamSize = 0;

// Function prototypes
void clearScreen();
void pauseScreen();
void managePokemonList();
void manageTeam();
void viewAllPokemon();
void addNewPokemon();
void updatePokemon();
void deletePokemon();
void savePokemonList();
void loadPokemonList();
void viewTeam();
void addPokemonToTeam();
void removePokemonFromTeam();
void saveTeam();
void loadTeam();

int main() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("|%39s|\n", "");
        printf("|            POKEMON PROJECT            |\n");
        printf("|%39s|\n", "");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n");
        printf("=========================================\n");
        printf("| %-37s |\n", "1. Manage Pokemon List");
        printf("| %-37s |\n", "2. Manage Team");
        printf("| %-37s |\n", "3. Exit");
        printf("=========================================\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        if (choice == 1) {
            managePokemonList();
        }
        else if (choice == 2) {
            manageTeam();
        }
        else if (choice == 3) {
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
            pauseScreen();
        }
    }
    return 0;
}

// Utility functions
void clearScreen() {
    system(CLEAR);
}

void pauseScreen() {
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

// Pokemon List Management
void managePokemonList() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n---- Pokemon List Manager ----\n");
        printf("1. View All Pokemon\n");
        printf("2. Add New Pokemon\n");
        printf("3. Update Pokemon\n");
        printf("4. Delete Pokemon\n");
        printf("5. Save Changes\n");
        printf("6. Load Pokemon List\n");
        printf("0. Back\n");
        printf("Enter Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            pauseScreen();
            continue;
        }
        if (choice == 1) {
            viewAllPokemon();
        }
        else if (choice == 2) {
            addNewPokemon();
        }
        else if (choice == 3) {
            updatePokemon();
        }
        else if (choice == 4) {
            deletePokemon();
        }
        else if (choice == 5) {
            savePokemonList();
        }
        else if (choice == 6) {
            loadPokemonList();
        }
        else if (choice == 0) {
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
            pauseScreen();
        }
    }
}

// Pokemon List Operations
void viewAllPokemon() {
    clearScreen();
    if (totalPokemons == 0) {
        printf("No Pokemon in the list.\n");
        pauseScreen();
        return;
    }
    printf("\n--- All Pokemon ---\n");
    printf("%-6s %-15s %-10s %-6s %-7s %-8s %s\n", "ID", "NAME", "TYPE", "HP", "ATTACK", "DEFENSE", "DESCRIPTION");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < totalPokemons; i++) {
        printf("%-6d %-15s %-10s %-6d %-7d %-8d %s\n", pokemons[i].id, pokemons[i].name, pokemons[i].type, pokemons[i].hp, pokemons[i].attack, pokemons[i].defense, pokemons[i].description);
    }
    pauseScreen();
}

void addNewPokemon() {
    clearScreen();
    if (totalPokemons >= MAX_POKEMON) {
        printf("Pokemon list is full!\n");
        pauseScreen();
        return;
    }
    struct Pokemon p;
    printf("Enter 4-Digit ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf("%s", p.name);
    printf("Enter Type: ");
    scanf("%s", p.type);
    printf("Enter HP: ");
    scanf("%d", &p.hp);
    printf("Enter Attack: ");
    scanf("%d", &p.attack);
    printf("Enter Defense: ");
    scanf("%d", &p.defense);
    printf("Enter Description: ");
    scanf(" %[^\n]", p.description);
    pokemons[totalPokemons++] = p;
    printf("%s added successfully!\n", p.name);
    pauseScreen();
    FILE *file = fopen("pokemon_list.csv", "a");
    if (file != NULL) {
        fprintf(file, "%d,%s,%s,%d,%d,%d,%s\n", p.id, p.name, p.type, p.hp, p.attack, p.defense, p.description);
        fclose(file);
    }
    else {
        printf("Error.\n");
    }
}

void updatePokemon() {
    clearScreen();
    int id, found = 0;
    printf("Enter the ID of the Pokemon to update: ");
    scanf("%d", &id);
    for (int i = 0; i < totalPokemons; i++) {
        if (pokemons[i].id == id) {
            found = 1;
            printf("Enter new Name: ");
            scanf("%s", pokemons[i].name);
            printf("Enter new Type: ");
            scanf("%s", pokemons[i].type);
            printf("Enter new HP: ");
            scanf("%d", &pokemons[i].hp);
            printf("Enter new Attack: ");
            scanf("%d", &pokemons[i].attack);
            printf("Enter new Defense: ");
            scanf("%d", &pokemons[i].defense);
            printf("Enter new Description: ");
            scanf(" %[^\n]", pokemons[i].description);
            printf("%s updated successfully!\n", pokemons[i].name);
            pauseScreen();
            return;
        }
    }
    if (!found) {
        printf("Pokemon with ID %d not found.\n", id);
        pauseScreen();
    }
}

void deletePokemon() {
    clearScreen();
    int id, found = 0;
    printf("Enter the ID of the Pokemon to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < totalPokemons; i++) {
        if (pokemons[i].id == id) {
            found = 1;
            char deletedName[30];
            strcpy(deletedName, pokemons[i].name); // save name before shifting
            for (int j = i; j < totalPokemons - 1; j++) {
                pokemons[j] = pokemons[j + 1];
            }
            totalPokemons--;
            printf("%s deleted successfully!\n", deletedName);
            pauseScreen();
            return;
        }
    }
    if (!found) {
        printf("Pokemon with ID %d not found.\n", id);
        pauseScreen();
    }
}

void savePokemonList() {
    clearScreen();
    FILE *file = fopen("pokemon_list.csv", "w");
    if (file == NULL) {
        printf("Error saving Pokemon list.\n");
        pauseScreen();
        return;
    }
    for (int i = 0; i < totalPokemons; i++) {
        fprintf(file, "%d,%s,%s,%d,%d,%d,%s\n", pokemons[i].id, pokemons[i].name, pokemons[i].type, pokemons[i].hp, pokemons[i].attack, pokemons[i].defense, pokemons[i].description);
    }
    fclose(file);
    printf("Pokemon list saved successfully!\n");
    pauseScreen();
}

void loadPokemonList() {
    clearScreen();
    FILE *file = fopen("pokemon_list.csv", "r");
    if (file == NULL) {
        printf("No saved Pokemon list found.\n");
        pauseScreen();
        return;
    }
    totalPokemons = 0;
    while (totalPokemons < MAX_POKEMON &&
           fscanf(file, "%d,%29[^,],%19[^,],%d,%d,%d,%99[^\n]\n",
                  &pokemons[totalPokemons].id, pokemons[totalPokemons].name, pokemons[totalPokemons].type,
                  &pokemons[totalPokemons].hp, &pokemons[totalPokemons].attack,
                  &pokemons[totalPokemons].defense, pokemons[totalPokemons].description) == 7) {
        totalPokemons++;
    }
    fclose(file);
    printf("Pokemon list loaded successfully!\n");
    pauseScreen();
}

// Team Management
void manageTeam() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n---- Team Manager ----\n");
        printf("1. View Team\n");
        printf("2. Add Pokemon to Team\n");
        printf("3. Remove Pokemon from Team\n");
        printf("4. Save Team\n");
        printf("5. Load Team\n");
        printf("0. Back\n");
        printf("Enter Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            pauseScreen();
            continue;
        }
        if (choice == 1) {
            viewTeam();
        } else if (choice == 2) {
            addPokemonToTeam();
        } else if (choice == 3) {
            removePokemonFromTeam();
        } else if (choice == 4) {
            saveTeam();
        } else if (choice == 5) {
            loadTeam();
        } else if (choice == 0) {
            break;
        } else {
            printf("Invalid choice. Try again.\n");
            pauseScreen();
        }
    }
}

// View the current team
void viewTeam() {
    clearScreen();
    printf("\n--- Your Team ---\n");
    if (teamSize == 0) {
        printf("Your team is empty.\n");
        pauseScreen();
        return;
    }
    printf("%-6s %-15s %-10s %-6s %-7s %-8s\n", "ID", "NAME", "TYPE", "HP", "ATTACK", "DEFENSE");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < teamSize; i++) {
        printf("%-6d %-15s %-10s %-6d %-7d %-8d\n", team[i].id, team[i].name, team[i].type, team[i].hp, team[i].attack, team[i].defense);
    }
    pauseScreen();
}

// Add a Pokemon to the team
void addPokemonToTeam() {
    clearScreen();
    if (teamSize >= MAX_TEAM) {
        printf("Your team is full! Remove a Pokemon before adding a new one.\n");
        pauseScreen();
        return;
    }
    int id;
    printf("Enter the ID of the Pokemon to add to your team: ");
    scanf("%d", &id);
    for (int i = 0; i < totalPokemons; i++) {
        if (pokemons[i].id == id) {
            team[teamSize++] = pokemons[i];
            printf("%s has been added to your team!\n", pokemons[i].name);
            pauseScreen();
            return;
        }
    }
    printf("Pokemon with ID %d not found in the list.\n", id);
    pauseScreen();
}

// Remove a Pokemon from the team
void removePokemonFromTeam() {
    clearScreen();
    if (teamSize == 0) {
        printf("Your team is empty.\n");
        pauseScreen();
        return;
    }
    int id, found = 0;
    printf("Enter the ID of the Pokemon to remove from your team: ");
    scanf("%d", &id);
    for (int i = 0; i < teamSize; i++) {
        if (team[i].id == id) {
            found = 1;
            printf("%s has been removed from your team.\n", team[i].name);
            for (int j = i; j < teamSize - 1; j++) {
                team[j] = team[j + 1];
            }
            teamSize--;
            pauseScreen();
            return;
        }
    }
    if (!found) {
        printf("Pokemon with ID %d not found in your team.\n", id);
    }
    pauseScreen();
}

// Save the current team to file
void saveTeam() {
    clearScreen();
    FILE *file = fopen("my_team.csv", "w");
    if (!file) {
        printf("Error saving team.\n");
        pauseScreen();
        return;
    }
    for (int i = 0; i < teamSize; i++) {
        fprintf(file, "%d,%s,%s,%d,%d,%d,%s\n",
                team[i].id, team[i].name, team[i].type,
                team[i].hp, team[i].attack, team[i].defense, team[i].description);
    }
    fclose(file);
    printf("Team saved successfully!\n");
    pauseScreen();
}

// Load team from file
void loadTeam() {
    clearScreen();
    FILE *file = fopen("my_team.csv", "r");
    if (file == NULL) {
        printf("No saved team found. Starting with an empty team.\n");
        pauseScreen();
        return;
    }
    teamSize = 0;
    while (teamSize < MAX_TEAM &&
           fscanf(file, "%d,%29[^,],%19[^,],%d,%d,%d,%99[^\n]\n",
                  &team[teamSize].id, team[teamSize].name, team[teamSize].type,
                  &team[teamSize].hp, &team[teamSize].attack,
                  &team[teamSize].defense, team[teamSize].description) == 7) {
        teamSize++;
    }
    fclose(file);
    printf("Team loaded successfully!\n");
    pauseScreen();
}