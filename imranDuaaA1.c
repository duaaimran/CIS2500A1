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


/* Task 1: This function must read the information from a text file called a1Data.txt and store them in the array called dataZoo, where each element of the array is of type struct Animal. There are 100 lines in the given text file, where each line stores information of a single
animal.*/
int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES]){
  FILE *fp; // Initialize file pointer
  fp = fopen(fName, "r"); // Open the file for reading
  if (fp == NULL){
    printf("Error: unable to open file %s\n", fName);
    return -1; // Return -1 if file not found (abnormal exit)
  }

  char line[100]; // Initialize a string to store each line of the file
  int i = 0; // Initialize a counter to keep track of the current line number

  while (fgets(line, sizeof(line), fp) != NULL && i < NUM_SAMPLES){
    
    //To get animal name
    char *feature = strtok(line, " "); // Split the line into tokens separated by spaces
    strcpy(dataZoo[i].animalName, feature); // Copy the first animal name into dataZoo[i].animalName
    
    // To get features
    for (int j = 0; j < NUM_FEATURES; j++){
      feature = strtok(NULL, " "); // Get the next feature value
      dataZoo[i].features[j] = atoi(feature); //Stores the feature as an integer in dataZoo[i].features[j]
    }

    // To get class label
    feature = strtok(NULL, " ");
    dataZoo[i].classLabel = atoi(feature);
    i++;
  }
  fclose(fp);
  return 1;
}

/* Task 2: Given the array dataZoo populated with data read in Task 1, and a feature number, this function generates the mean and mode of that feature and outputs it to the calling function. It returns -1 if the given feature number is incorrect. Note that the valid features are numbered from 1 to 16.*/

int generateStatisticsFeatureX (struct Animal dataZoo [NUM_SAMPLES], int whichFeature, float * mean, int * mode){
  int count[16] = {0};
  int sum = 0;
  int maxCount = 0;
  int maxCountIndex = 0;

  // Returns -1 if the given feature number is incorrect.
  if(whichFeature < 1 || whichFeature > NUM_FEATURES){
    return -1;
  }

  for (int i = 0; i < NUM_SAMPLES; i++){
    sum += dataZoo[i].features[whichFeature - 1]; // Adds the value of the current feature to the sum
    count[dataZoo[i].features[whichFeature -1]]++; // Increments the count of the current feature value
  }

  *mean = (float)sum /NUM_SAMPLES; // Calculates the mean of the feature

  for (int i = 0; i < NUM_FEATURES; i++){
    if (count[i] > maxCount){
      maxCount = count[i];
      maxCountIndex = i;
    }
  }

  *mode = maxCountIndex; // Stores the mode of the feature in the mode pointer

  return 1;
}

/* Task 3: This function takes the zoo dataset and displays its class distribution as a histogram as shown. Note that member name classLabel in struct Animal stores the class label for each sample or row. There are 40 rows with classLabel as 1, 20 rows with classLabel l as 2, and so on.*/
void classDistribution (struct Animal dataZoo [NUM_SAMPLES]){
  int classes[NUM_CLASSES] = {0};

  // Count occurences of each class
  for(int i = 0; i < NUM_SAMPLES; i++){
    classes[dataZoo[i].classLabel-1]++;
  }

  // Create a copy of classes
  int dummyClassCount[NUM_CLASSES] = {0};
  for(int i = 0; i < NUM_CLASSES; i++){
    dummyClassCount[i] = classes[i];
  }

  // Find the maximum class count
  int maxClassCount = dummyClassCount[0];
  for(int i = 0; i < NUM_CLASSES; i++){
    if(classes[i] > maxClassCount){
      maxClassCount = classes[i];
    }
  }

  // Increment maxClassCount to ensure the loop runs the correct number of times
  maxClassCount++;

  // Print the histogram
  while(maxClassCount != 0){
    for(int i = 0; i < 7; i++){
      if(classes[i] == maxClassCount){
        printf("  *  ");
      }
      else if(maxClassCount-1 == dummyClassCount[i]){
        printf(" (%d) ", dummyClassCount[i]);
      }
      else{
        printf("     ");
      }
      printf("      ");
    }
    printf("\n");
    
    // Decrement classes for classes with current maxClassCount
    for(int i = 0; i < 7; i++){
      if(classes[i] == maxClassCount){
        classes[i]--;
      }
    }
    
    // Decrement maxClassCount for the next iteration
    maxClassCount--;
  }
  
  // Print class labels
  for(int i = 0; i < NUM_CLASSES; i++){
    printf("Class %d    ", i+1);
  }
}

/* Task 4: This function computes and returns the Euclidean distance between 2 arrays, each with 16 features. */
float euclideanDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]){
  float distance = 0;

  // Calculate the Euclidean distance between the two vectors
  for (int i = 0; i < NUM_FEATURES; i++){
    float diff = vector1[i] - vector2[i];
    distance = distance + (diff * diff);
  }
  distance = sqrt(distance);
  
  return distance;
}

/* Task 5: This function finds the number of values in vector1 that differ from corresponding values in vector2 */
int hammingDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]){
  int hammingDistance = 0;

  // Count the number of values that differ between the two vectors
  for (int i = 0; i < NUM_FEATURES; i++){
    if (vector1[i] != vector2[i]){
      hammingDistance++;
    }
  }
  
  return hammingDistance;
}

/* Task 6: This function returns the Jaccard Similarity. */
float jaccardSimilarity (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]){
  float jaccardSimilarity =0;
  int oneToOne = 0;
  int zeroToZero = 0;

  // Count the number of values that are in both vectors
  for (int i = 0; i < NUM_FEATURES; i++){
    if (vector1[i] == vector2[i]){
      if (vector1[i] == 1){
        oneToOne++;
      }
      if (vector1[i] == 0){
        zeroToZero++;
      }
    }
  }
  
  // Calculate the Jaccard Similarity
  jaccardSimilarity = (float)oneToOne / (NUM_FEATURES - (float)zeroToZero);
  return jaccardSimilarity;
}

/* Task 7: This function finds the k nearest neighbors of a sample. The function returns the indices of the k nearest neighbors in the array */
// Sorting function from chatGPT
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]){
  float distances[NUM_SAMPLES];
  int indices[NUM_SAMPLES];

  // Calculate the distance between the new sample and each animal in the dataZoo
  for (int i = 0; i < NUM_SAMPLES; i++){
    switch (whichDistanceFunction){
      case 1:
        distances[i] = euclideanDistance(dataZoo[i].features, newSample);
        break;
      case 2:
        distances[i] = hammingDistance(dataZoo[i].features, newSample);
        break;
      case 3:
        distances[i] = jaccardSimilarity(dataZoo[i].features, newSample);
        break;
      default:
        printf("Invalid distance function selected.\n");
        exit(1);
    }
    indices[i] = i;
  }

  // Sort distances and maintain indices
  for (int i = 0; i < NUM_SAMPLES - 1; i++) {
    for (int j = 0; j < NUM_SAMPLES - i - 1; j++) {
      if (distances[j] > distances[j + 1]) {
        // Swap distances
        float tempDistance = distances[j];
        distances[j] = distances[j + 1];
        distances[j + 1] = tempDistance;

        // Swap indices
        int tempIndex = indices[j];
        indices[j] = indices[j + 1];
        indices[j + 1] = tempIndex;
      }
    }
  }
  // Copy the indices of the k nearest neighbors
  for (int i = 0; i < k; i++){
    kNearestNeighbors[i] = indices[i];
    printf("Nearest Neighbor %d: Index %d\n", i + 1, kNearestNeighbors[i]);
  }
}

/* Task 8: This function predicts the class of a new sample. */
int predictClass (struct Animal dataZoo [NUM_SAMPLES], int neighborsForNewSample [NUM_SAMPLES], int newSample [NUM_FEATURES], int k){
  int classCount[NUM_CLASSES] = {0};
  int maxCount = 0;
  int predictedClass = -1;

  // Count the occurrences of each class in the k nearest neighbors
  for (int i = 0; i < k; i++){
    int index = neighborsForNewSample[i];
    int neighboringClass = dataZoo[index].classLabel;
    classCount[neighboringClass - 1]++;
  }

  // Find the class with the maximum count
  for (int i = 0; i < NUM_CLASSES; i++) {
    if (classCount[i] > maxCount) {
      maxCount = classCount[i];
      predictedClass = i + 1;
    }
  }
  
  return predictedClass;
}

/* Task 9: This function returns the accuracy of the kNN classifier. */
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], struct Animal testData [NUM_TEST_DATA], int k){
  int correctPredictions = 0;
  int neighborsForNewSample[NUM_SAMPLES];
  int kNearestNeighbors[NUM_SAMPLES];
  int predictedClass;

  for (int i = 0; i < NUM_TEST_DATA; i++) {
    findKNearestNeighbors(dataZoo, testData[i].features, k, 1, neighborsForNewSample);
    // Predict the class of each test sample
    predictedClass = predictClass(dataZoo, kNearestNeighbors, testData[i].features, k);
    if (predictedClass == testData[i].classLabel) {
      correctPredictions++;
    }
  }

  float accuracy = (float)correctPredictions / NUM_TEST_DATA * 100.0;
  return accuracy;
}
