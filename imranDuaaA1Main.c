#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "givenA1.h"
#define NUM_FEATURES 16   //not including animal name and class label
#define NUM_SAMPLES 100      // total number of samples / rows in the given zoo dataset
#define NUM_CLASSES 7        // total number of class labels in zoo dataset
#define NUM_TEST_DATA 20     // total number of samples / rows in the test dataset - you need this for task 9
#define MAX_LENGTH_ANIMAL_NAME 50


int main(void) {
  struct Animal dataZoo[NUM_SAMPLES];
  struct Animal testData[NUM_TEST_DATA];
  int whichFeature;
  float mean;
  int mode;
  int vector1[] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
  int vector2[] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1};
  float distance;
  int newSample[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
  int k;
  int whichDistanceFunction;
  int kNearestNeighbors[NUM_SAMPLES];
  int neighboursForNewSample[NUM_SAMPLES];
  int choice;

  printf("Welcome to the Zoo!\n");
  printf("*************MENU**************\n");
  printf("1. Read the zoo data from a file\n");
  printf("2. Generate statistics for a feature\n");
  printf("3. Class distribution\n");
  printf("4. Euclidean distance\n");
  printf("5. Hamming distance\n");
  printf("6. Jaccard similarity\n");
  printf("7. Find k nearest neighbors\n");
  printf("8. Predict class\n");
  printf("9. Find accuracy\n");
  printf("Please choose Option 1 from the list to start: ");
  scanf("%d", &choice);

  while (choice != 1){
    printf("Please choose Option 1 from the list to start: ");
    scanf("%d", &choice);
  }
  if (choice == 1){
    readFromFile("a1Data.txt", dataZoo);
    printf("Zoo data read from file.\n");
  }
  
  while (choice >= 1 && choice <= 9){
    printf("\n*************MENU**************\n");
    printf("1. Read the zoo data from a file\n");
    printf("2. Generate statistics for a feature\n");
    printf("3. Class distribution\n");
    printf("4. Euclidean distance\n");
    printf("5. Hamming distance\n");
    printf("6. Jaccard similarity\n");
    printf("7. Find k nearest neighbors\n");
    printf("8. Predict class\n");
    printf("9. Find accuracy\n");
    printf("Please choose an option from the menu: ");
    scanf("%d", &choice);
    switch(choice) {
      case 2:
        printf("Please choose a feature to generate statistics for: ");
        scanf("%d", &whichFeature);
        generateStatisticsFeatureX (dataZoo, whichFeature, &mean, &mode);
        printf("Mean %.2f\nMode: %d\n", mean, mode);
        break;
    case 3:
        classDistribution(dataZoo);
        break;
      case 4:
        distance = euclideanDistance(vector1, vector2);
        printf("Euclidean distance: %.2f\n", distance);
        break;
      case 5:
        distance = hammingDistance(vector1, vector2);
        printf("Hamming Distance: %.2f\n", distance);
        break;
      case 6:
        distance = jaccardSimilarity(vector1, vector2);
        printf("Jaccard Similarity: %.2f\n", distance);
        break;
      case 7:
        printf("Enter the value of k: ");
        scanf("%d", &k);
        printf("Enter the distance function to use\n 1. Euclidean\n 2. Hamming\n 3. Jaccard\nEnter your choice: ");
        scanf(" %d", &whichDistanceFunction);
        findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, kNearestNeighbors);
        break;
      case 8:
        printf("Enter a value for k: ");
        scanf("%d", &k);
        int predictedClass = predictClass(dataZoo, kNearestNeighbors, newSample, k);
        printf("Predicted class: %d\n", predictedClass);
        break;
      case 9:
        readFromFile("testData.txt", testData);
        printf("Enter a value for k: ");
        scanf("%d", &k);
        printf("Accuracy: %.2f%%\n", findAccuracy(dataZoo, testData, k));
        break;
      default:
        printf("Invalid choice. Exiting...\n");
        choice = 11;
        break;
    }
  }
  return 0;
}
