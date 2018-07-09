#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class CircularList {


	struct personNode {
		string name;
		struct personNode* next;
	};
	
	personNode* head = NULL;
	personNode* tail;

public:
	int count = 0;
	int called = 0; //number of times display has been called.
	void deletePerson(int skips, ofstream& file);
	void createPerson(string name, ofstream& file);
	void displayList(ofstream& file);
};


void CircularList::createPerson(string name, ofstream& file) {
	personNode *newPerson = new personNode;

	newPerson->name = name;

	if (head == NULL) {
		head = newPerson;
		tail = newPerson;
		newPerson->next = head;
	}

	else {
		tail->next = newPerson;
		tail = newPerson;
		tail->next = head;
		
	}
	count++;
	//cout << newPerson->name<< endl;

}
void CircularList::deletePerson(int skips, ofstream& file) {

	personNode *curr = head;

	//cout << endl<<"Original head is: " << head->name << endl;

	if (!head) {
		cout << "List is empty" << endl;
		return;
	}

	else if (count==1) {

		file << "Cannot execute only person" << endl;
	}

	else if (count>1){

		

		personNode *prevPerson =NULL;

		for (int i = 1;i <= count;i++) {
			prevPerson = curr;
			curr = curr->next;
			if (i == skips) {
				prevPerson->next = curr->next;
				head = prevPerson;
				//cout << endl << "Head is :" << head->name << endl;
				file << curr->name << " Executed."<<endl;
				delete curr;
				count--;
				break;
			}
			else if (i == skips - count) {
				prevPerson->next = curr->next;
				head = prevPerson;
				//cout << endl << "Head is :" << head->name << endl;
				file << curr->name<<" executed." << endl;
				delete curr;
				count--;
				break;
			}

		}
		
	}

}

void CircularList::displayList(ofstream& file) {
	
	personNode *temp = head;
	called++;

	if (called==1) {
		if (count == 1)
			file << head->name<<endl;
		else{
			while (temp->next != head) {
				file << temp->name << endl;
				temp = temp->next;
			}
		}
		
	}
	else{
		file<< head->name << " survived";
	}
	


}


int main() {


	ofstream newFile;
	newFile.open("output.txt");

	CircularList list;

	string fileName = "Third.txt";

	ifstream inFile;

	inFile.open(fileName);
	int numberOfPeople;

	string numPeople;

	vector<int> skips;
	vector<string> people;
	
	getline(inFile, numPeople);

	numberOfPeople = stoi(numPeople);

	while (!inFile.eof()) {

		string read;
		getline(inFile, read);
		
		

		if (!isalpha(read[0])) {
			skips.push_back(stoi(read));
		}
		
		else if(read != "AC") {
			people.push_back(read);
			list.createPerson(read, newFile);
		}

	}

	list.displayList(newFile);
	newFile << endl;

	for (int i = 0;i < skips.size();i++) {

		list.deletePerson(skips[i], newFile);
		
	}
	newFile << endl;
	list.displayList(newFile);

	newFile.close();


	getchar();
	return 0;
}