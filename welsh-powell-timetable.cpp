#include <bits/stdc++.h>

using namespace std;

// Function to generate the timetable using the Welsh-Powell algorithm.
void generateTimetable(const vector<int> &subjects, const vector<string> &teachers)
{
	// Map to store subjects taught by each teacher
	map<string, vector<int>> teacherSubjectMap;
	int subjectIndex = 0;

	// Assign subjects to teachers in a cyclic manner
	for (int i = 0; i < subjects.size(); i++)
	{
		teacherSubjectMap[teachers[i % (teachers.size())]].push_back(subjects[i]);
	}

	// Print the num of subjects taught by each teacher
	for (auto t : teacherSubjectMap)
	{
		cout << t.first << ' ' << t.second.size() << endl;
	}

	// Create an adjacency list representing subject dependencies
	vector<vector<int>> adj_subject(subjects.size());

	// Connect subjects taught by the same teacher
	for (auto it : teacherSubjectMap)
	{
		string teacher = it.first;
		vector<int> subjectList = it.second;
		if (subjectList.size() == 1)
			continue;
		for (int i = 0; i < subjectList.size(); i++)
		{
			for (int j = i + 1; j < subjectList.size(); j++)
			{
				adj_subject[subjectList[i]].push_back(subjectList[j]);
				adj_subject[subjectList[j]].push_back(subjectList[i]);
			}
		}
	}

	// Calculate the degree of each subject
	vector<pair<int, int>> degree;
	for (int i = 0; i < adj_subject.size(); i++)
	{
		degree.push_back({adj_subject[i].size(), i});
	}
	sort(degree.begin(), degree.end());

	// Color the subjects using Welsh-Powell algorithm
	vector<int> color(subjects.size(), -1);
	int clr = 0;
	for (int ind = 0; ind < subjects.size(); ind++)
	{
		int node1 = degree[ind].second;
		if (color[node1] != -1)
			continue;

		color[node1] = clr;

		for (int i = ind + 1; i < subjects.size(); i++)
		{
			int node2 = degree[i].second;

			if (color[node2] != -1)
				continue;

			bool flag = true;

			for (auto it : adj_subject[node2])
			{
				if (color[it] == clr)
					flag = false;
			}
			if (flag)
				color[node2] = clr;
		}
		clr++;
	}

	// Define colors and time accordingly for visual representation
	vector<pair<string, string>> c = {{"red", "10:00 - 11:00"}, {"blue", "11:00 - 12:00"}, {"green", "12:00 - 13:00"}, {"yellow", "13:00 - 14:00"}};

	// Print the assigned colors for each subject
	for (int i = 0; i < color.size(); i++)
	{
		cout << "Subject" << i << " " << c[color[i]].first << " " << c[color[i]].second << endl;
	}
}

int main()
{
	vector<int> subjects = {0, 1, 2, 3, 4};
	vector<string> teachers = {"Teacher1", "Teacher2", "Teacher3", "Teacher4"};

	generateTimetable(subjects, teachers);

	return 0;
}