#include <iostream>
#include <vector>
#include <string>
using namespace std;
bool IsSafe(int N, int M, int AllocationMat[][100], int MaxMat[][100], int AvailableMat[], int NeedMat[][100], vector<int> &SafeSequenceVector)
{
	int * WorkMat = AvailableMat;
	int FinishMat[100] = { 0 };
	int flag = 0;

	for (int l = 0; l<N; l++)
	{
		for (int i = 0; i<N; i++)
		{
			if (FinishMat[i] == 0)
			{
				flag = 1;
				for (int j = 0; j<M; j++)
				{
					if (NeedMat[i][j]>WorkMat[j])
					{
						flag = 0;
					}
				}
				if (flag == 1)
				{
					SafeSequenceVector.push_back(i);
					for (int k = 0; k<M; k++)
					{
						WorkMat[k] += AllocationMat[i][k];
						FinishMat[i] = 1;
					}

				}
			}
		}
	}

	for (int k = 0; k<N; k++)
	{
		if (FinishMat[k] == 0)
		{
			return 0;
		}
	}
	return 1;
}




bool CanGrant(int N, int M, int Process, int RequestMat[], int AllocationMat[][100], int MaxMat[][100], int AvailableMat[], int NeedMat[][100], vector<int> &SafeSequenceVector2)
{
	for (int i = 0; i<M; i++)
	{
		if (RequestMat[i]>NeedMat[Process][i] || RequestMat[i]>AvailableMat[i])
		{
			return 0;
		}

	}
	for (int i = 0; i<M; i++)
	{
		AvailableMat[i] -= RequestMat[i];
		AllocationMat[Process][i] += RequestMat[i];
		NeedMat[Process][i] -= RequestMat[i];
	}
	return IsSafe(N, M, AllocationMat, MaxMat, AvailableMat, NeedMat, SafeSequenceVector2);

}




int main()
{
	string s;

	cout << "Enter the number of processes:" << endl;
	getline(cin, s);
	int N = stoi(s);

	cout << "Enter the number of types of resources:" << endl;
	getline(cin, s);
	int M = stoi(s);

	int AllocationMat[100][100];
	string snum;
	int numspaces=0;
	int j;

	for (int k = 0; k<N; k++)
	{
		cout << "Enter the Allocation Matrix of P" << k << ":" << endl;
		getline(cin, s);
		j = 0;
		snum = "";
		for (int i = 0; i<s.length(); i++)

		{
			if (s[i] != ' ')
			{
				snum += s[i];
				if (i == s.length() - 1)
				{
					int num = stoi(snum);
					AllocationMat[k][j] = num;
				}
			}
			else
			{
				int num = stoi(snum);
				AllocationMat[k][j] = num;
				j++;
				snum = "";
				numspaces += 1;
			}
		}

	}





	int MaxMat[100][100];
	j = 0;

	for (int k = 0; k<N; k++)
	{
		cout << "Enter the Maximum Matrix of P" << k << ":" << endl;
		getline(cin, s);
		j = 0;
		snum = "";
		for (int i = 0; i<s.length(); i++)

		{
			if (s[i] != ' ')
			{
				snum += s[i];
				if (i == s.length() - 1)
				{
					int num = stoi(snum);
					MaxMat[k][j] = num;
				}
			}
			else
			{
				int num = stoi(snum);
				MaxMat[k][j] = num;
				j++;
				snum = "";
				numspaces += 1;
			}
		}

	}




	int AvailableMat[100];
	int AvailableMat2[100];
	j = 0;


	cout << "Enter the Available Matrix:" << endl;
	getline(cin, s);
	j = 0;
	snum = "";
	for (int i = 0; i<s.length(); i++)

	{
		if (s[i] != ' ')
		{
			snum += s[i];
			if (i == s.length() - 1)
			{
				int num = stoi(snum);
				AvailableMat[j] = num;
				AvailableMat2[j] = num;

			}
		}
		else
		{
			int num = stoi(snum);
			AvailableMat[j] = num;
			AvailableMat2[j] = num;
			j++;
			snum = "";
			numspaces += 1;
		}
	}

	int NeedMat[100][100];
	cout << "The Need Matrix is:" << endl;
	char ss = 'A';
	cout << "    ";
	for (int i = 0; i<M; i++)
	{
		cout << ss << "  ";
		ss += 1;
	}
	cout << endl;
	for (int i = 0; i<N; i++)
	{
		cout << "P" << i << "  ";
		for (int j = 0; j<M; j++)
		{
			NeedMat[i][j] = MaxMat[i][j] - AllocationMat[i][j];
			cout << NeedMat[i][j] << "  ";
		}
		cout << endl;
	}

	vector <int> SafeSequenceVector;
	vector <int> SafeSequenceVector2;


	cout << "Press 1 if you want to know if the system is safe or 0 if not." << endl;
	getline(cin, s);
	if (s == "1")
	{
		if (IsSafe(N, M, AllocationMat, MaxMat, AvailableMat, NeedMat, SafeSequenceVector))
		{
			cout << "Yes, Safe State <";
			for (int i = 0; i<SafeSequenceVector.size(); i++)
			{
				cout << "P" << SafeSequenceVector[i];
				if (i != SafeSequenceVector.size() - 1)
					cout << ",";
			}
			cout << ">" << endl;
		}

		else
			cout << "No, Not Safe." << endl;
	}



	cout << "Press 1 if you want to ask about immediate request or 0 if not." << endl;
	getline(cin, s);
	if (s == "1")
	{
		cout << "Enter the number of the process that wants a request:" << endl;
		getline(cin, s);
		int requestingProcess = stoi(s);
		cout << "Enter the request:" << endl;
		getline(cin, s);

		int RequestMat[100];
		j = 0;
		snum = "";
		for (int i = 0; i<s.length(); i++)

		{
			if (s[i] != ' ')
			{
				snum += s[i];
				if (i == s.length() - 1)
				{
					int num = stoi(snum);
					RequestMat[j] = num;

				}
			}
			else
			{
				int num = stoi(snum);
				RequestMat[j] = num;
				j++;
				snum = "";
				numspaces += 1;
			}
		}

		if (CanGrant(N, M, requestingProcess, RequestMat, AllocationMat, MaxMat, AvailableMat2, NeedMat, SafeSequenceVector2))
		{
			cout << "Your request can be granted with safe state, Safe State <P" << requestingProcess << "req,";

			for (int i = 0; i<SafeSequenceVector2.size(); i++)
			{
				cout << "P" << SafeSequenceVector2[i];
				if (i != SafeSequenceVector2.size() - 1)
					cout << ",";
			}
			cout << ">" << endl;
		}
		else
		{
			cout << "Your request cannot be granted.";
		}

	}
	system("pause");
	return 0;
}


