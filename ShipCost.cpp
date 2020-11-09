// Nicholas DeRoss 
// CSCI 130 
// Fall Semester 

//Shipping Redux 


//This program takes in values from a file 
// and outputs the cost for a specific shipping company // 

#include <iomanip>

#include <iostream>

#include <string>

#include <cmath>

#include <fstream>

using namespace std;

double findRate(double packWeight); // Function Prototype for rate function

double findDiscount(char cusType, int distanceShipped); // Function prototype for finding discount 

int main(void)

{

  string nameOfCustomer; // Name of the customer 
  char cusType; // Type of Customer 
  int packWeight; // Weight of Package Shipped 
  int distanceShipped; // Distance package is being shipped 
  double packRate; // Rate charged (based on weight) 
  double costNoDiscount; // Cost before discount applied (if aplicable) 
  double finalAmmountDue; // Final ammount charged to the customer 
  double discount; // Discount (based on customer type and miles shipped) 
  string inFileName; // Input File name 
  string outFileName; // Output file name 
  int weightIsValid; // Checks weight, if valid, sets to 0, if not 1 
  int cusIsValid; // Checks customer type, if valid sets to 0, if not 1
  int distanceIsValid; // Checks distance, if valid sets to 0, if not 1 
  int errorTotal; // Total number of customer cases that result in an error 
  int isValid; // All three "isValid" statements culiminate here
  double totalDiscount; // Total discount when run through entire file 
  double totalCost; // Total cost of entire shipment file 

  ifstream shipIn; // Declares input stream 
  ofstream amtDueOut; // Declares output stream 

  cout << "Enter the name of the input file ";

  cin >> inFileName; // Takes in name of input file from user 

  cout << "Enter the name of the output file ";

  cin >> outFileName; // Takes in name of output file from user 

  if (inFileName != "ship.dat") {
    cout << "Incorrect File Name" << endl; // Checks input file name, must be "ship.dat" 
    //      or the program will exit 
    return 0;
  } else

    shipIn.open(inFileName.c_str()); // opens input file 

  amtDueOut.open(outFileName.c_str()); // opens output file 	

  {
    amtDueOut << "Customer" //This block will output the basic structure of 
      <<
      setw(10) << "Customer" // the output table // 
      <<
      setw(10) << "Package" <<
      setw(10) << "Distance" <<
      setw(20) << "   Amount" << endl;

    amtDueOut << "  Name" <<
      setw(10) << " Type" <<
      setw(12) << "Weight" <<
      setw(10) << "Shipped" <<
      setw(11) << "Discount" <<
      setw(8) << "Due" <<
      endl;

    (errorTotal = 0); // This block serves as a primer to the ammounts that will be calculated within the loop 

    (totalCost = 0.00);

    (totalDiscount = 0.00);

    shipIn >> nameOfCustomer >> cusType >> packWeight >> distanceShipped; // Reads in values from file 

  }

  while (!shipIn.eof()) { // The loop here will only run until the end of "ship.dat" is reached 

    (discount = 0.00);

    (finalAmmountDue = 0.00);

    if ((cusType == 'V') or(cusType == 'R') or(cusType == 'N')) {
      cusIsValid = 0;
    } // checks customer type 
    else

    if (cusType != 'V' || 'N' || 'R') {
      cusIsValid = 1;
    }

    if ((packWeight > 0) and(packWeight <= 25)) {
      weightIsValid = 0;
    } //Checks package weight 
    else {
      weightIsValid = 1;
    }

    if ((distanceShipped >= 10) and(distanceShipped <= 3000)) {
      distanceIsValid = 0;
    } // Checks distance 
    else

    {
      distanceIsValid = 1;
    }

    // The following determmines the value of "isValid" If all of the isValid variables are 0, isValid = 0, else isValid = 1

    if ((distanceIsValid == 0) and(cusIsValid == 0) and(weightIsValid == 0))

    {
      isValid = 0;
    } else

    {
      isValid = 1;
    }

    // If isValid is 1, we run through the error outputs, and outputs the entered input + the error message for 
    //   each particular case 

    if (isValid == 1) {

      (errorTotal = errorTotal++);

      if (cusIsValid == 1)

      {
        amtDueOut << setw(8) << left << nameOfCustomer << right << setw(6) <<
          cusType << setw(11) <<
          packWeight << setw(11) <<
          distanceShipped << setw(6) << "$" <<
          discount << setw(8) << "$" <<
          finalAmmountDue << "  " << "*** Customer Type Invalid ***" << endl;
      }

      if (weightIsValid == 1) {
        amtDueOut << setw(8) << left << nameOfCustomer << right << setw(6) <<
          cusType << setw(11) <<
          packWeight << setw(11) <<
          distanceShipped << setw(6) << "$" << discount << setw(8) << "$" <<
          finalAmmountDue << "  " << "*** Weight Invalid ***" << endl;
      }

      if (distanceIsValid == 1) {
        amtDueOut << setw(8) << nameOfCustomer << setw(6) <<
          cusType << setw(11) <<
          packWeight << setw(11) <<
          distanceShipped << setw(6) << "$" << discount << setw(8) << "$" <<
          finalAmmountDue << "  " << "*** Distance Invalid ***" << endl;
      }

    }

    // If isValid = 0, the previous code block is skipped completly, and the calculations for price are done

    if (isValid == 0) {

      packRate = findRate(packWeight); // calls to function findRate, returns package rate 

      discount = findDiscount(cusType, distanceShipped); // calls to function findDiscount, returns discount

      costNoDiscount = ceil(double(distanceShipped) / 500) * packRate; // calculates the cost of the package before discount applied 

      discount = (costNoDiscount * discount); // converts discount from its own value to a percentage of the
      // cost of shipping, and takes that percentage off final cost 

      finalAmmountDue = (costNoDiscount - discount); // subtracts discount from final cost 

      totalDiscount = (totalDiscount + discount); // adds the discount for this particular customer to the total 

      totalCost = (totalCost + finalAmmountDue); // adds cost of this package shipment from this customer to the total for the file 

      // The following outputs the values returned for the cost to ship, and discount (if availible) 

      amtDueOut << fixed << setw(8) << left << nameOfCustomer << right <<
        setw(6) << cusType <<
        setw(11) << packWeight <<
        setw(11) << distanceShipped <<
        setw(6) << "$" <<
        fixed << setprecision(2) <<
        discount << setw(8) <<
        "$" << finalAmmountDue << endl;

    }

    shipIn >> nameOfCustomer >> cusType >> packWeight >> distanceShipped; // Reads in the next customer case, returns to top 

  } // Loop closed here // 

  amtDueOut << endl;

  amtDueOut << setw(46) << "Total:" << "    " << setw(8) << "Total:" << endl; // Outputs totals of file after loop is closed 
  // and test cases are all passed in 
  amtDueOut << setw(42) << "$" << totalDiscount << setw(6) << "$" << totalCost << endl;

  amtDueOut << endl;

  amtDueOut << "Number of Error Cases: " << errorTotal << endl; // Outputs total number of error cases 

  amtDueOut << endl;

  return 0; // Program end. 
}

// This function will calculate the rate of the shipment //  
//
//Preconditions - package weight 
//
// Postconditions - package rate 

double findRate(double packWeight) {

  double packRate;

  if ((packWeight > 0) and(packWeight <= 2)) {
    packRate = 1.10;
  } else {
    if ((packWeight > 2) and(packWeight <= 6)) {
      packRate = 2.20;
    } else {
      if ((packWeight > 6) and(packWeight <= 10)) {
        packRate = 3.70;
      } else {
        if ((packWeight > 10) and(packWeight <= 20)) {
          packRate = 4.80;
        } else {
          return 0;
        }
      }
    }
  }
  return packRate;
}

// This function will calculate the discount, or return a zero if parameters of discount are not met // 
//
// Preconditions cusType, and distanceShipped 
// 
// Postconditions - discount 

double findDiscount(char cusType, int distanceShipped) {

  double discount;

  if (cusType == 'N') {
    jo
    discount = 0.00;
  } else {
    if ((cusType == 'R') and(distanceShipped >= 1000)) {
      discount = 0.05;
    } else {
      if ((cusType == 'V') and(distanceShipped >= 500)) {
        discount = 0.12;
      } else {
        discount = 0.00;
      }
    }
  }
  return discount;
}
