#include <iostream>
using namespace std;
int main()
{
	int n;
	cout << "Enter the number of point you are aáout to enter: ";
	cin >> n;

	//*vectors e dinamichen masiv, ne znam dali ste go vzemali, no taka se pravi
	double *vectors = new double[n], x, y, max_vector,buff;

	// tova ti e vuvejdaneto na tochkite
	for (unsigned i = 0; i < n; i++)
	{
		cout << "Enter x" << i + 1 << ": ";
		cin >> x;
		cout << "Enter y" << i + 1 << ": ";
		cin >> y;
		vectors[i] = sqrt(x*x + y*y);
	}
	
	// tova ti namira nai-dulgiq vector v max_vector
	max_vector = vectors[0];
	for (unsigned i = 0; i < n; i++) if (vectors[i] > max_vector) max_vector = vectors[i];
	
	// tova ti sortita masiva ot vectorite vectors v nizhodqsht red
	for (unsigned i = 0; i < n - 1; i++)
		for (unsigned k = i + 1; k < n; k++)
		{
			//ako ne vi dava da polzvate swap da razmenqsh chisla polzvai tova dolu
			if (vectors[i] < vectors[k])
			{
				buff = vectors[i];
				vectors[i] = vectors[k];
				vectors[k] = buff;
			}
			// az bih go napravil taka, ako vi dava da polzvate swap
			/*if (vectors[i] < vectors[k]) swap(vectors[i], vectors[k]);*/
		}

	//tuk print-q nai-dulgiq vector
	cout << endl << "Longest vector: " << max_vector << endl;
	for (unsigned i = 0; i < n; i++)
	{
		cout << i + 1 << ") " << vectors[i] << endl;
	}

	//tuk triq masiva poneje e zadelen v hesh-a, no ako ne ste go uchili moje da ne go pishesh,
	//no e greshka da ne go pishesh poprincip, ti si precini
	delete[] vectors;
}