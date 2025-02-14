/*
Movie ticket boking
Ritwik Sai G (RA2311026010483)
Harshavardhan Reddy (RA2311026010498)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure
struct book {
  char code[20];
  char name[20];
  char date[20];
  int cost;
} b;

int seat = 60;

// Functions
void add_movies();    // for inserting movie details
void viewAllMovies(); // for view all data
void find();          // for finding data
void book_ticket();   // for booking tickets
void old_record();    // for view old records of users, booked tickets
void modify_movie();  // for modifying movie
void delete_movie();  // for deleting movie
void find_booking_transaction(); // for finding booking transaction

long long BookingID = 1;

// Main Function
      int main() {
        int userType, ch;
        char password[20];

        do {
            printf("\n*****************************************************************"
                   "*******");
            printf("\n");
            printf("\t \t \t \t MOVIE TICKET BOOKING ");
            printf("\n");
            printf("\n*****************************************************************"
                   "*******");

            printf("\n\nPress <1> Admin");
            printf("\nPress <2> User");
            printf("\nPress <0> Exit \n");

            printf("\nEnter your Choice :: ");
            scanf("%d", &userType);

            switch (userType) {
                case 1: // Admin Menu
                    printf("\nEnter the password: ");
                    scanf("%s", password);

                    // Check if the entered password matches
                    if (strcmp(password, "1234") == 0) {
                        do {
                            printf("\n*****************************************************************"
                                   "*******");
                            printf("\n");
                            printf("\t \t \t \t ADMIN PANEL");
                            printf("\n");
                            printf("\n*****************************************************************"
                                   "*******");

                            printf("\n\nPress <1> Add Movie");
                            printf("\nPress <2> View All Movie");
                            printf("\nPress <3> Find Movie ");
                            printf("\nPress <4> Modify Movie details");
                            printf("\nPress <5> Delete Movie");
                            printf("\nPress <0> Exit \n");

                            printf("\nEnter your Choice :: ");
                            scanf("%d", &ch);

                            switch (ch) {
                                case 1:
                                    add_movies();
                                    break;

                                case 2:
                                    viewAllMovies();
                                    break;

                                case 3:
                                    find();
                                    break;

                                case 4:
                                    modify_movie();
                                    break;

                                case 5:
                                    delete_movie();
                                    break;

                                case 0:
                                    break;

                                default:
                                    system("clear");
                                    printf("Wrong choice !\n");
                                    break;
                            }
                        } while (ch != 0);
                    } else {
                        printf("\nIncorrect password. Access denied!\n");
                    }
                    break;


    case 2: // User Menu
      do {
        printf("\n*****************************************************************"
               "*******");
        printf("\n");
        printf("\t \t \t \t USER PANEL");
        printf("\n");
        printf("\n*****************************************************************"
               "*******");

        printf("\n\nPress <1> View All Movie");
        printf("\nPress <2> Book Ticket");
        printf("\nPress <3> View All transactions");
        printf("\nPress <4> Find Booking transaction");
        printf("\nPress <0> Exit \n");

        printf("\nEnter your Choice :: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
          viewAllMovies();
          break;

        case 2:
          book_ticket();
          break;

        case 3:
          old_record();
          break;

        case 4:
          find_booking_transaction();
          break;

        case 0:
          break;

        default:
          system("clear");
          printf("Wrong choice !\n");
          break;
        }
      } while (ch != 0);
      break;

    case 0:
      exit(0);
      break;

    default:
      system("clear");
      printf("Wrong choice !\n");
      break;
    }
  } while (userType != 0);
}

// for inserting movie details
void add_movies() {
  FILE *fp;
  struct book b;
  printf("Enter movie code :- \n");
  scanf("%s", b.code);
  printf("Enter movie name :- \n");
  scanf("%s", b.name);
  printf("Enter Release Date:- \n");
  scanf("%s", b.date);
  printf("Enter Ticket Price:- \n");
  scanf("%d", &b.cost);

  fp = fopen("data.txt", "a");

  if (fp == NULL) {
    printf("File not Found");
  } else {
    fprintf(fp, "%s\n %s\n %s\n %d \n", b.code, b.name, b.date, b.cost);
    printf("\nRecord inserted Sucessfull");
  }
  printf("\n");
  fclose(fp);
}

// to view all movies
void viewAllMovies() {
  char ch;
  FILE *fp;

  fp = fopen("data.txt", "r");
  if (fp == NULL) {
    printf("file is not found !");
    exit(1);

  } else {
    system("clear");
    while ((ch = fgetc(fp)) != EOF)
      printf("%c", ch);
  }
  fclose(fp);
}

// to find movie based on movie code
void find() {
  char search_code[20];
  struct book movie;
  int found = 0;

  printf("Enter the movie code to find: ");
  scanf("%s", search_code);

  FILE *fp = fopen("data.txt", "r");
  if (fp == NULL) {
    printf("\nFile not found!\n");
    return;
  }

  while (fscanf(fp, "%s %s %s %d", movie.code, movie.name, movie.date,
                &movie.cost) != EOF) {
    if (strcmp(search_code, movie.code) == 0) {
      found = 1;
      printf("\nMovie Code: %s\n", movie.code);
      printf("Movie Name: %s\n", movie.name);
      printf("Release Date: %s\n", movie.date);
      printf("Ticket Price: %d\n", movie.cost);
      break; // Exit the loop after finding the movie
    }
  }

  if (!found) {
    printf("Movie with code %s not found.\n", search_code);
  }

  fclose(fp);
}

// for ticket booking
//  Structure for user information
struct user {
  long long booking_id;
  char name[100];
  char mobile[20];
  char movie[20];
  int num_tickets;
  int total_cost;
};

// Function to book tickets
void book_ticket() {
  FILE *movieFile, *userFile;
  char movie_code[20];
  struct book movie;
  struct user user_info;

  printf("Enter the movie code to book tickets: ");
  scanf("%s", movie_code);

  // Check if the movie code exists
  movieFile = fopen("data.txt", "r");
  if (movieFile == NULL) {
    printf("\nMovie database file not found!\n");
    return;
  }

  int movieFound = 0;
  while (fscanf(movieFile, "%s %s %s %d", movie.code, movie.name, movie.date,
                &movie.cost) != EOF) {
    if (strcmp(movie.code, movie_code) == 0) {
      movieFound = 1;
      break;
    }
  }
  fclose(movieFile);

  if (movieFound) {
    // Generate a unique booking ID
    long long booking_id = BookingID;
    BookingID++;

    printf("Enter your name: ");
    scanf("%s", user_info.name);
    printf("Enter your mobile number: ");
    scanf("%s", user_info.mobile);
    printf("Enter the number of tickets to book: ");
    scanf("%d", &user_info.num_tickets);

    // Calculate the total cost
    user_info.total_cost = user_info.num_tickets * movie.cost;

    // Write user data to a file with booking ID
    userFile = fopen("user_data.txt", "a");
    if (userFile == NULL) {
      printf("User data file not found!\n");
      return;
    }
    fprintf(userFile,
            "Booking ID: %lld\nMovie: %s\nName: %s\nMobile: %s\nNumber of "
            "Tickets: %d\nTotal Cost: %d\n\n",
            booking_id, movie.name, user_info.name, user_info.mobile,
            user_info.num_tickets, user_info.total_cost);
    fclose(userFile);

    printf("\nTickets booked successfully!\n\n");
    printf("Booking ID: %lld\n", booking_id);
    printf("User Name: %s\nMobile number: %s", user_info.name,
           user_info.mobile);
    printf("\nMovie Name: %s\n", movie.name);
    printf("Number of Tickets: %d\n", user_info.num_tickets);
    printf("Total Cost: %d\n", user_info.total_cost);
  } else {
    printf("Movie with code %s not found.\n", movie_code);
  }
}

// Function for finding booking transaction using booking ID
void find_booking_transaction() {
  FILE *userFile;
  struct user user_info;
  long long booking_id;
  int found = 0;

  printf("Enter the Booking ID: ");
  scanf("%lld", &booking_id);

  userFile = fopen("user_data.txt", "r");
  if (userFile == NULL) {
    printf("User data file not found!\n");
    return;
  }

  while (fscanf(userFile,
                "Booking ID: %lld\nMovie: %s\nName: %s\nMobile: %s\nNumber of "
                "Tickets: %d\nTotal Cost: %d\n\n",
                &user_info.booking_id, user_info.movie, user_info.name,
                user_info.mobile, &user_info.num_tickets,
                &user_info.total_cost) != EOF) {
    if (user_info.booking_id == booking_id) {
      found = 1;
      break;
    }
  }
  fclose(userFile);

  if (found) {
    printf("\nBooking ID: %lld\n", user_info.booking_id);
    printf("Movie: %s\n", user_info.movie); // Display the correct movie name
    printf("Name: %s\n", user_info.name);
    printf("Mobile: %s\n", user_info.mobile);
    printf("Number of Tickets: %d\n", user_info.num_tickets);
    printf("Total Cost: %d\n", user_info.total_cost);
  } else {
    printf("Booking with ID %lld not found.\n", booking_id);
  }
}

// for view all user transactions
void old_record() {
  FILE *userFile;
  char ch;

  userFile = fopen("user_data.txt", "r");
  if (userFile == NULL) {
    printf("\nUser data file not found!\n");
    return;
  }
  printf("\n");
  while ((ch = fgetc(userFile)) != EOF) {
    putchar(ch);
  }

  fclose(userFile);
}

// to modify movie details
void modify_movie() {
  char search_code[20];
  struct book movie;

  printf("Enter the movie code to modify: ");
  scanf("%s", search_code);

  FILE *fp = fopen("data.txt", "r");
  FILE *temp_file =
      fopen("temp_data.txt", "w"); // Temporary file for writing modified data

  if (fp == NULL) {
    printf("\nFile not found!\n");
    return;
  }

  int found = 0;

  while (fscanf(fp, "%s %s %s %d", movie.code, movie.name, movie.date,
                &movie.cost) != EOF) {
    if (strcmp(search_code, movie.code) == 0) {
      found = 1;
      printf("\nCurrent Movie Details:\n");
      printf("Movie Code: %s\n", movie.code);
      printf("Current Movie Name: %s\n", movie.name);
      printf("Current Release Date: %s\n", movie.date);
      printf("Current Ticket Price: %d\n", movie.cost);

      printf("\nEnter the new movie name: ");
      scanf("%s", movie.name);
      printf("Enter the new release date: ");
      scanf("%s", movie.date);
      printf("Enter the new ticket price: ");
      scanf("%d", &movie.cost);

      // Write the updated movie details to the temporary file
      fprintf(temp_file, "%s %s %s %d\n", movie.code, movie.name, movie.date,
              movie.cost);

      printf("Movie details updated successfully!\n");
    } else {
      // Copy the existing movie details to the temporary file
      fprintf(temp_file, "%s %s %s %d\n", movie.code, movie.name, movie.date,
              movie.cost);
    }
  }

  fclose(fp);
  fclose(temp_file);

  // Rename the temporary file to "data.txt" to replace the original file
  remove("data.txt");
  rename("temp_data.txt", "data.txt");

  if (!found) {
    printf("Movie with code %s not found.\n", search_code);
  }
}

// to delete movie details
void delete_movie() {
  char delete_code[20];
  struct book movie;

  printf("Enter the movie code to delete: ");
  scanf("%s", delete_code);

  FILE *fp = fopen("data.txt", "r");
  FILE *temp_file =
      fopen("temp_data.txt", "w"); // Temporary file for writing modified data

  if (fp == NULL) {
    printf("File not found!\n");
    return;
  }

  int found = 0;

  while (fscanf(fp, "%s %s %s %d", movie.code, movie.name, movie.date,
                &movie.cost) != EOF) {
    if (strcmp(delete_code, movie.code) == 0) {
      found = 1;
      printf("\nMovie with code %s has been deleted.\n", delete_code);
    } else {
      // Copy the existing movie details (except the one to be deleted) to the temporary file
      fprintf(temp_file, "%s %s %s %d\n", movie.code, movie.name, movie.date,
              movie.cost);
    }
  }

  fclose(fp);
  fclose(temp_file);

  // Rename the temporary file to "data.txt" to replace the original file
  remove("data.txt");
  rename("temp_data.txt", "data.txt");

  if (!found) {
    printf("Movie with code %s not found.\n", delete_code);
  }
}