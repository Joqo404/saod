#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <vector>


using namespace std;
const int N = 4000;

struct record {
    char author[12];
    char title[32];
    char publisher[16];
    short int year;
    short int num_of_page;
};

struct Node
{
	record* Record;
	Node* next;
};

struct Vertex {
    record *data;
    Vertex *left;
    Vertex *right;
    int balance;
};

void scan_database(record* Array, record** A, int n)
{
	FILE* database;
	database = fopen("testBase1.dat", "rb");
	fread((record*)Array, sizeof(record), n, database);
	fclose(database);
	for (int i = 0; i < n; i++)
	{
		A[i] = &Array[i];
	}
}

string prompt(const string &str) {
    cout << str;
    cout << "\n> ";
    string ans;
    cin >> ans;
    return ans;
}

int strcomp(const string &str1, const string &str2, int len = -1) {
    if (len == -1) {
        len = (int) str1.length();
    }
    for (int i = 0; i < len; ++i) {
        if (str1[i] == '\0' and str2[i] == '\0') {
            return 0;
        } else if (str1[i] == ' ' and str2[i] != ' ') {
            return -1;
        } else if (str1[i] != ' ' and str2[i] == ' ') {
            return 1;
        } else if (str1[i] < str2[i]) {
            return -1;
        } else if (str1[i] > str2[i]) {
            return 1;
        }
    }
    return 0;
}

void quicksort(record** arr, int l, int r) 
{
    record *x;
    record *temp;
    int i = l;
    x = arr[i];
    int j = r;
    while (i <= j)
    {
        while (strcmp(arr[i]->author , x->author) < 0)
        {
            i += 1;
        }
        while (strcmp(arr[j]->author , x->author) > 0)
        {
            j -= 1;
        }
        if (i <= j)
        {
           
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i += 1;
            j -= 1;
        }
    }
    if (l < j)
    {
        quicksort(arr,l,j);
    }
    if (i < r) 
    {
        quicksort(arr,i,r);
    }
}

void print_record(record* Record)
{
	cout << Record->author
		<< "  " << Record->title
		<< "  " << Record->publisher
		<< "  " << Record->year 
		<< "  " << Record->num_of_page << "\n";
}

void print_database(record* A, int n)
{
	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		cout << i << ". " << A[i].author << " " << A[i].title << " " << A[i].publisher << " " << A[i].year << "\n";

		if ((i % 20 == 0) && (i != 0))
		{
			cout << "\nContinue? 0/1: ";
			scanf("%d", &temp);
			if (temp == 0) break;
			else system("cls");
		}
	}
	system("pause");
}

void print_array(record** A, int n)
{
	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		cout << i << ". " << A[i]->author << " " << A[i]->title << " " << A[i]->publisher << " " << A[i]->year << "\n";
		if ((i % 20 == 0) && (i != 0))
		{
			cout << "\nContinue? 0/1: ";
			scanf("%d", &temp);
			if (temp == 0) break;
			else system("cls");
		}
	}
	system("pause");
}

void search_array(record** A, Node* root, int k)
{
	Node* p = root;
	for (int i = 0; i < k; i++)
	{
		A[i] = (p->Record);
		p = p->next;
	}
}

int quick_search(record *arr[], const string &key) {
    int l = 0;
    int r = N - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (strcomp(arr[m]->author, key, 3) < 0) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    if (strcomp(arr[r]->author, key, 3) == 0) {
        return r;
    }
    return -1;
}

void search(record *arr[], int &ind, int &n) {
    Node *head = nullptr, *tail = nullptr;
    string key;
    do {
        key = prompt("Input search key (3 characters of author)");
    } while (key.length() != 3);
    ind = quick_search(arr, key);
    if (ind == -1) {
        cout << "Not found\n";
    } else {
        head = new Node{arr[ind], nullptr};
        tail = head;
        int i;
        for (i = ind + 1; i < 4000 and strcomp(arr[i]->author, key, 3) == 0; ++i) {
            tail->next = new Node{arr[i], nullptr};
            tail = tail->next;
        }
        n = i - ind;
        record *find_arr[n];
        Node *p = head;
    	for (int i = 0; i < n; i++) {
        	find_arr[i] = p->Record;
        	p = p->next;
    	}
        print_array(find_arr, n);
    }
}

void dbd_add(record *data, Vertex *&p) {
    static int vr = 1;
    static int hr = 1;
    if (!p) {
        p = new Vertex{data, nullptr, nullptr, 0};
        vr = 1;
    } else if (data->year < p->data->year) {
        dbd_add(data, p->left);
        if (vr == 1) {
            if (p->balance == 0) {
                Vertex *q = p->left;
                p->left = q->right;
                q->right = p;
                p = q;
                q->balance = 1;
                vr = 0;
                hr = 1;
            } else {
                p->balance = 0;
                vr = 1;
                hr = 0;
            }
        } else {
            hr = 0;
        }
    } else if (data->year >= p->data->year) {
        dbd_add(data, p->right);
        if (vr == 1) {
            p->balance = 1;
            hr = 1;
            vr = 0;
        } else if (hr == 1) {
            if (p->balance == 1) {
                Vertex *q = p->right;
                p->balance = 0;
                q->balance = 0;
                p->right = q->left;
                q->left = p;
                p = q;
                vr = 1;
                hr = 0;
            } else {
                hr = 0;
            }
        }
    }
}

void Print_tree(Vertex* p) {
	static int i = 1;
	if (p!=NULL) {
		Print_tree(p->left);
		print_record(p->data);
		Print_tree(p->right);
	}
}

void search_in_tree(Vertex* root, short int key) 
{
	if (root) 
	{
		if (root->data->year > key) {
			search_in_tree(root->left, key);
		}
		else if (root->data->year < key) {
			search_in_tree(root->right, key);
		}
		else if (root->data->year == key) {
			search_in_tree(root->left, key);
			print_record(root->data);
			search_in_tree(root->right, key);
		}
	}
}

void rmtree(Vertex *root) {
    if (root) {
        rmtree(root->right);
        rmtree(root->left);
        delete root;
    }
}

void tree(record** arr, int k)
{
    Vertex *root = nullptr;
    for (int i = 0; i < k; ++i) {
        dbd_add(arr[i], root);
    }
    
    Print_tree(root);
    short int key;
	printf("input key: ");
	cin >> key;
	
	search_in_tree(root, key);	
	
	system("pause");
	rmtree(root);
}

void shannon(const int n, double p[], int Length[], char c[][20]) {
    double q[n];
    q[0] = 0;
    Length[0] = -floor(log2(p[0]));
    for (int i = 1; i < n; ++i) {
        q[i] = q[i - 1] + p[i - 1];
        Length[i] = -floor(log2(p[i]));
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < Length[i - 1]; ++j) {
            q[i - 1] *= 2;
            c[i - 1][j] = floor(q[i - 1]) + '0';
            if (q[i - 1] >= 1) {
                q[i - 1] -= 1;
            }
        }

    }
}

unordered_map<char, int> get_char_counts_from_file(const string &file_name, int &file_size, int n = N) {
    ifstream file(file_name, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }
    char ch_arr[sizeof(record) * n];
    file.read((char *) ch_arr, sizeof(record) * n);
    file.close();

    unordered_map<char, int> counter_map;
    file_size = 0;
    for (auto ch : ch_arr) {
        counter_map[ch]++;
        file_size++;
    }
    return counter_map;
}

vector<pair<double, char>> calc_probabilities(const unordered_map<char, int> &counter_map, int count) {
    vector<pair<double, char>> probabilities;
    probabilities.reserve(counter_map.size());
    for (auto i : counter_map) {
        probabilities.emplace_back(make_pair((double) i.second / count, i.first));
    }
    return probabilities;
}

void coding() {
    int file_size;
    unordered_map<char, int> counter_map;
    counter_map = get_char_counts_from_file("testBase1.dat", file_size);

    auto probabilities = calc_probabilities(counter_map, file_size);
    counter_map.clear();

    sort(probabilities.begin(), probabilities.end(), greater<pair<double, char>>());
    cout << "Probabil.  char\n";
    for (auto i : probabilities) {
        cout << fixed << i.first << " | " << i.second << '\n';
    }

    const int n = (int) probabilities.size();

    auto c = new char[n][20];
    auto Length = new int[n];
    auto p = new double[n];
    for (int i = 0; i < n; ++i) {
        p[i] = probabilities[i].first;
    }

    double shen = 0;
    shannon(n, p, Length, c);
    cout << "\nShannon Code:\n";
    cout << "\nCh  Prob      Code\n";
    double avg_len = 0;
    double entropy = 0;
    for (int i = 0; i < n; i++) {
        avg_len += Length[i] * p[i];
        entropy -= p[i] * log2(p[i]);
        printf("%c | %.5lf | ", probabilities[i].second, p[i]);
        for (int j = 0; j < Length[i]; ++j) {
            printf("%c", c[i][j]);
        }
        cout << '\n';
        shen += p[i];
    }
    cout << "Average length = " << avg_len << '\n'
         << "Entropy = " << entropy << '\n'
         << "Average length < entropy + 1\n"
         << "n = " << n << endl;

}

int main()
{
	int n = 4000, temp, ind, k = -1;
	
	record Array[n];
	record* A[n];
    
    scan_database(Array, A, n);
    quicksort(A, 0, n-1);
    
    while (1)
	{

		cout << "1 - Print BD " << endl;
		cout << "2 - Print Array " << endl;
		cout << "3 - Search " << endl;
		cout << "4 - Tree " << endl;
		cout << "5 - Coding " << endl;
		cout << "0 - End " << endl;
		scanf("%d", &temp);
		switch (temp)
		{
		case 1:
			print_database(Array, N);
			break;
		case 2:
			print_array(A, N);	
			break;
		case 3:
			search(A, ind, k);
			break;
		case 4:
			if(k < 0)
			{
				cout << "Search first\n";
				system("pause");
			}
			else
				tree(&A[ind], k);
			break;
		case 5:
			coding();
			system("pause");
            break;	
		default:
			return 1;
		}
		system("cls");
	}
    
    return 0;
}
