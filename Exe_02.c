#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <sys/wait.h>   

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {
        // Parent process
        close(pipe1[0]); 
        close(pipe2[1]); 

        char choice;
        float input1, input2;
        printf("Choose shape (C - Circle, T - Triangle, S - Square, R - Rectangle): ");
        scanf(" %c", &choice);
        choice = toupper(choice);

        float inputs[2] = {0, 0}; 

        switch (choice) {
            case 'C':
                printf("Enter radius of circle: ");
                scanf("%f", &input1);
                inputs[0] = input1;
                break;
            case 'T':
                printf("Enter base and height of triangle: ");
                scanf("%f %f", &input1, &input2);
                inputs[0] = input1;
                inputs[1] = input2;
                break;
            case 'S':
                printf("Enter side of square: ");
                scanf("%f", &input1);
                inputs[0] = input1;
                break;
            case 'R':
                printf("Enter length and width of rectangle: ");
                scanf("%f %f", &input1, &input2);
                inputs[0] = input1;
                inputs[1] = input2;
                break;
            default:
                printf("Invalid choice.\n");
                close(pipe1[1]);
                close(pipe2[0]);
                wait(NULL);
                exit(1);
        }

        // Write choice and inputs to child
        write(pipe1[1], &choice, sizeof(choice));
        write(pipe1[1], inputs, sizeof(inputs));
        close(pipe1[1]);

        // Read result from child
        float area;
        read(pipe2[0], &area, sizeof(area));
        close(pipe2[0]);

        // Print result
        switch (choice) {
            case 'C':
                printf("Area of circle = %.2f\n", area);
                break;
            case 'T':
                printf("Area of triangle = %.2f\n", area);
                break;
            case 'S':
                printf("Area of square = %.2f\n", area);
                break;
            case 'R':
                printf("Area of rectangle = %.2f\n", area);
                break;
        }

        wait(NULL);  // Wait for child to finish
    } else {
        // Child process
        close(pipe1[1]); 
        close(pipe2[0]); 

        char choice;
        float inputs[2];
        float area = 0;

        read(pipe1[0], &choice, sizeof(choice));
        read(pipe1[0], inputs, sizeof(inputs));
        close(pipe1[0]);

        switch (choice) {
            case 'C':
                area = M_PI * inputs[0] * inputs[0];  // πr²
                break;
            case 'T':
                area = 0.5 * inputs[0] * inputs[1];   // ½ * base * height
                break;
            case 'S':
                area = inputs[0] * inputs[0];         // side²
                break;
            case 'R':
                area = inputs[0] * inputs[1];         // length * width
                break;
            default:
                area = 0; // invalid choice, area 0
        }

        write(pipe2[1], &area, sizeof(area));
        close(pipe2[1]);
        exit(0);
    }

    return 0;
}
