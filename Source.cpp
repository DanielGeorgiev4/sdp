#include <iostream>
using namespace std;
int main()
{
	int n;
	cout << "Enter the number of point you are a�out to enter: ";
	cin >> n;

	//*vectors � ��������� �����, �� ���� ���� ��� �� �������, �� ���� �� �����
	double *vectors = new double[n], x, y, max_vector,buff;

	// ���� �� � ���������� �� �������
	for (unsigned i = 0; i < n; i++)
	{
		cout << "Enter x" << i + 1 << ": ";
		cin >> x;
		cout << "Enter y" << i + 1 << ": ";
		cin >> y;
		vectors[i] = sqrt(x*x + y*y);
	}
	
	// ���� �� ������ ���-������ ������ � max_vector
	max_vector = vectors[0];
	for (unsigned i = 0; i < n; i++) if (vectors[i] > max_vector) max_vector = vectors[i];
	
	// ���� �� ������� ������ �� ��������� vectors � �������� ���
	for (unsigned i = 0; i < n - 1; i++)
		for (unsigned k = i + 1; k < n; k++)
		{
			//��� �� �� ���� �� ���������� swap �� �������� ����� ������� ���� ������
			if (vectors[i] < vectors[k])
			{
				buff = vectors[i];
				vectors[i] = vectors[k];
				vectors[k] = buff;
			}
			// �� ��� �� �������� ����, ��� �� ���� �� �������� swap
			/*if (vectors[i] < vectors[k]) swap(vectors[i], vectors[k]);*/
		}

	//��� �� ������
	cout << endl << "Longest vector: " << max_vector << endl;
	for (unsigned i = 0; i < n; i++)
	{
		cout << i + 1 << ") " << vectors[i] << endl;
	}

	//��� ���� ������ ������ � ������� � hesh-a, �� ��� �� ��� �� ����� ���� �� �� �� �����,
	//�� � ������ �� �� �� ����� ���������, �� �� �������
	delete[] vectors;
}