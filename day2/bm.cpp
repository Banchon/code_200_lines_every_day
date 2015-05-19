#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char* argv[])
{
	if(argc < 2) {
		cout << "Usage: " << argv[0] << " bitSequence" <<endl;
		return -1;
	}

	string bitSequence = argv[1];
	vector<int> an;
	for(int i = 0; i < bitSequence.size(); i++) {
		if(bitSequence[i] == '0')
			an.push_back(0);
		else
			an.push_back(1);
	}
	cout << "an = ";
	for(vector<int>::iterator it = an.begin(); it != an.end(); it++)
		cout << *it;
	cout << endl;

	int N = bitSequence.size();
	cout << "N = " << N << endl;

	vector<int> ln_vec;
	vector<vector<int> >  fx_vec;
	vector<int> dn_vec;

	ln_vec.push_back(0);
	
	vector<int> fx;
	fx.push_back(1);

	fx_vec.push_back(fx);

	for(int n = 0; n < N; n++) {
		int dn = 0;

		for(int j = 0; j <= ln_vec[n]; j++)
			dn += fx_vec[n][j] * an[n - j];
		dn %= 2;
		dn_vec.push_back(dn);

		if(dn == 0) {
			ln_vec.push_back(ln_vec[n]);
			fx_vec.push_back(fx_vec[n]);
		}
		else {
			bool is_zero = true;

			for (vector<int>::iterator it = ln_vec.begin(); it != ln_vec.end(); it++) {
				if(*it != 0) {
					is_zero = false;
					break;
				}
			}

			if(is_zero) {
				ln_vec.push_back(n + 1);
				vector<int> fx;
				for(int k = 0; k <= n + 1; k++) {
					if(k == 0 || k == n + 1)
						fx.push_back(1);
					else
						fx.push_back(0);
				}
				fx_vec.push_back(fx);
			}
			else
			{
				int i;
				for(i = ln_vec.size() - 2; i >= 0; i--) {
					if(ln_vec[i] != ln_vec[i+1])
						break;
				}

				int shift = n - i;
				vector<int> temp;
				for(int j = 0; j < shift; j++)
					temp.push_back(0);
				 
				for(vector<int>::iterator it = fx_vec[i].begin(); it != fx_vec[i].end(); it++)
					temp.push_back(*it);

				int ln = ln_vec[n];
				ln_vec.push_back(ln > (n + 1 - ln) ? ln : (n + 1 - ln));

				vector<int> fx = fx_vec[n];
				if(fx.size() > temp.size()) {
					for(int j = 0; j < temp.size(); j++) {
						fx[j] += temp[j];
						fx[j] %= 2;
					}
					fx_vec.push_back(fx);	
				}
				else {
					for(int j = 0; j < fx.size(); j++) {
						temp[j] += fx[j];
						temp[j] %= 2;
					}
					fx_vec.push_back(temp);
				}
			}
		}
	}

	for(int i = 0; i < fx_vec.size(); i++) {
		cout << "f" << i << "(x) = ";
		vector<int> fix = fx_vec[i];
   		for(vector<int>::iterator it = fix.begin(); it != fix.end(); it++)
	 	  cout << *it;
 	 	cout << endl;

		cout << "l" << i << " = ";
  		cout << ln_vec[i] << endl;

		if( i != (fx_vec.size() -1))
			cout << "d" << i << " = " << dn_vec[i] << endl;

		cout << endl;
	}

   return 0;
}
