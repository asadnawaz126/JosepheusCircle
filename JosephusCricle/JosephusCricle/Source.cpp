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
	void deletePerson(int skips);
	void createPerson(string name);
	void displayList();
};


void CircularList::createPerson(string name) {
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
void CircularList::deletePerson(int skips) {

	personNode *curr = head;

	//cout << endl<<"Original head is: " << head->name << endl;

	if (!head) {
		cout << "List is empty" << endl;
		return;
	}

	else if (count==1) {

		curr = head->next;
		delete head;
		tail->next = curr;
		head = curr;
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
				cout << "Deleted: " << curr->name << endl;
				delete curr;
				count--;
				break;
			}
			else if (i == skips - count) {
				prevPerson->next = curr->next;
				head = prevPerson;
				//cout << endl << "Head is :" << head->name << endl;
				cout << "Deleted: " << curr->name << endl;
				delete curr;
				count--;
				break;
			}

		}
		
	}

}

void CircularList::displayList() {
	
	personNode *temp = head;

	if (count == 1) {
		cout << head->name<<" survived";
	}
	while (temp->next != head) {
		cout << temp->name << endl;
		temp = temp->next;
	}


}


int main() {

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
			list.createPerson(read);
		}

	}

	list.displayList();

	cout << endl;

	for (int i = 0;i < skips.size();i++) {

		list.deletePerson(skips[i]);
		
	}
	cout << endl;
	list.displayList();


	getchar();
	return 0;
}