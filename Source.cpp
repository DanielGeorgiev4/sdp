#include <iostream>
using namespace std;
int main()
{
	int n;
	cout << "Enter the number of point you are aбout to enter: ";
	cin >> n;

	//*vectors е динамичен масив, не знам дали сте ги вземали, но така се прави
	double *vectors = new double[n], x, y, max_vector,buff;

	// това ти е въвежданте на точките
	for (unsigned i = 0; i < n; i++)
	{
		cout << "Enter x" << i + 1 << ": ";
		cin >> x;
		cout << "Enter y" << i + 1 << ": ";
		cin >> y;
		vectors[i] = sqrt(x*x + y*y);
	}
	
	// това ти намира най-дългия вектор в max_vector
	max_vector = vectors[0];
	for (unsigned i = 0; i < n; i++) if (vectors[i] > max_vector) max_vector = vectors[i];
	
	// това ти сортира масива то векторите vectors в низходящ ред
	for (unsigned i = 0; i < n - 1; i++)
		for (unsigned k = i + 1; k < n; k++)
		{
			//ако не ви дава да използвате swap да разменяш числа ползвай това отдолу
			if (vectors[i] < vectors[k])
			{
				buff = vectors[i];
				vectors[i] = vectors[k];
				vectors[k] = buff;
			}
			// аз бих го направил така, ако ви дава да ползвате swap
			/*if (vectors[i] < vectors[k]) swap(vectors[i], vectors[k]);*/
		}

	//тук ги принтя
	cout << endl << "Longest vector: " << max_vector << endl;
	for (unsigned i = 0; i < n; i++)
	{
		cout << i + 1 << ") " << vectors[i] << endl;
	}

	//тук трия масива понеже е заделен в hesh-a, но ако не сте го учили може да не го пишеш,
	//но е грешка да не го пишеш попринцип, ти си прецени
	delete[] vectors;
}