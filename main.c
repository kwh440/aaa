#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MAX 100

void inputScores(int scores[], int *n);
int totalMarks(int scores[], int n);
float averageMarks(int scores[], int n);
void highestLowest(int scores[], int n, int *highest, int *lowest);
float median(int scores[], int n);
float standardDeviation(int scores[], int n);
void showGrades(int scores[], int n);
void gradeGraph(int scores[], int n);
float predictNextScore(int scores[], int n);

int main()
{
    int scores[MAX];
    int n = 0;
    int choice;
    int highest, lowest;


    printf("\n======= Student Score Analyzer =======\n");

    do
    {
        //printf("\n======= Student Score Analyzer =======\n");
        printf("1. Input scores\n");
        printf("2. Display total and average\n");
        printf("3. Display highest and lowest scores\n");
        printf("4. Display median\n");
        printf("5. Display standard deviation\n");
        printf("6. Show grades\n");
        printf("7. Exit\n");
        //printf("\n=======------------------------=======\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        //printf("\n=====------------------------=====\n");

        switch(choice)
        {
            case 1:
                inputScores(scores, &n);
                break;

            case 2:
                if(n > 0)
                {
                    printf("Total = %d\n", totalMarks(scores, n));
                    printf("Average = %.2f\n", averageMarks(scores, n));
                    printf("Predicted Next Score = %.2f\n",
                           predictNextScore(scores, n));
                }
                else
                    printf("Please input scores first.\n");
                break;

            case 3:
                if(n > 0)
                {
                    highestLowest(scores, n, &highest, &lowest);
                    printf("Highest = %d\n", highest);
                    printf("Lowest = %d\n", lowest);
                }
                else
                    printf("Please input scores first.\n");
                break;

            case 4:
                if(n > 0)
                    printf("Median = %.2f\n", median(scores, n));
                else
                    printf("Please input scores first.\n");
                break;

            case 5:
                if(n > 0)
                    printf("Standard Deviation = %.2f\n",
                           standardDeviation(scores, n));
                else
                    printf("Please input scores first.\n");
                break;

            case 6:
                if(n > 0)
                {
                    showGrades(scores, n);
                    showGradesAndGraph(scores, n);
                }
                else
                    printf("Please input scores first.\n");
                break;

            case 7:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

        printf("\n=========== Next Operation ===========\n");

    } while(choice != 7);



    return 0;
}

void inputScores(int scores[], int *n)
{
    int i;

    printf("Enter number of students: ");
    scanf("%d", n);

    for(i = 0; i < *n; i++)
    {
        do
        {
            printf("Enter mark for student %d (1-100): ", i + 1);
            scanf("%d", &scores[i]);

            if(scores[i] < 1 || scores[i] > 100)
                printf("Invalid mark! Try again.\n");

        } while(scores[i] < 1 || scores[i] > 100);
    }
}

int totalMarks(int scores[], int n)
{
    int sum = 0, i;

    for(i = 0; i < n; i++)
        sum += scores[i];

    return sum;
}

float averageMarks(int scores[], int n)
{
    return (float)totalMarks(scores, n) / n;
}

void highestLowest(int scores[], int n, int *highest, int *lowest)
{
    int i;

    *highest = scores[0];
    *lowest = scores[0];

    for(i = 1; i < n; i++)
    {
        if(scores[i] > *highest)
            *highest = scores[i];

        if(scores[i] < *lowest)
            *lowest = scores[i];
    }
}

float median(int scores[], int n)
{
    int temp[MAX];
    int i, j, swap;

    for(i = 0; i < n; i++)
        temp[i] = scores[i];

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(temp[j] > temp[j + 1])
            {
                swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    if(n % 2 == 1)
        return temp[n / 2];
    else
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
}

float standardDeviation(int scores[], int n)
{
    float avg = averageMarks(scores, n);
    float sum = 0;
    int i;

    for(i = 0; i < n; i++)
        sum += (scores[i] - avg) * (scores[i] - avg);

    return sqrt(sum / n);
}

void showGrades(int scores[], int n)
{
    int i;
    char grade;

    printf("\nStudent Grades:\n");

    for(i = 0; i < n; i++)
    {
        if(scores[i] >= 75)
            grade = 'A';
        else if(scores[i] >= 65)
            grade = 'B';
        else if(scores[i] >= 50)
            grade = 'C';
        else if(scores[i] >= 35)
            grade = 'S';
        else
            grade = 'F';

        printf("Student %d : %d -> %c\n",
               i + 1, scores[i], grade);
    }
}

void showGradesAndGraph(int marks[], int n)
{
    int countA = 0, countB = 0, countC = 0, countS = 0, countF = 0;
    int i;
    char grade;

    printf("\n--- Individual Grades ---\n");

    for (i = 0; i < n; i++)
    {
        if (marks[i] >= 75)
        {
            grade = 'A';
            countA++;
        }
        else if (marks[i] >= 65)
        {
            grade = 'B';
            countB++;
        }
        else if (marks[i] >= 50)
        {
            grade = 'C';
            countC++;
        }
        else if (marks[i] >= 35)
        {
            grade = 'S';
            countS++;
        }
        else
        {
            grade = 'F';
            countF++;
        }

        printf("Student %d: Score = %d, Grade = %c\n",
               i + 1, marks[i], grade);
    }

    printf("\n--- Grade Distribution Graph ---\n");

    printf("A (75+)  : ");
    for (i = 0; i < countA; i++) printf("*");
    printf(" (%d)\n", countA);

    printf("B (65-74): ");
    for (i = 0; i < countB; i++) printf("*");
    printf(" (%d)\n", countB);

    printf("C (50-64): ");
    for (i = 0; i < countC; i++) printf("*");
    printf(" (%d)\n", countC);

    printf("S (35-49): ");
    for (i = 0; i < countS; i++) printf("*");
    printf(" (%d)\n", countS);

    printf("F (<35)  :  ");
    for (i = 0; i < countF; i++) printf("*");
    printf(" (%d)\n", countF);
}
float predictNextScore(int scores[], int n)
{
    int i;
    float sum = 0;

    if(n >= 3)
    {
        for(i = n - 3; i < n; i++)
            sum += scores[i];

        return sum / 3;
    }

    for(i = 0; i < n; i++)
        sum += scores[i];

    return sum / n;
}
