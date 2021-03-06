/*IP CALCULATOR*/
//Проверка на полноту ввода

#include <iostream>
#include <bitset>
using namespace std;
bool stringIPtoARR(char ipStr[], int *ip);
bool verifySimbol(char strIP[]);
void print2CC(int *a);
void print10CC(int *a);
void printROW(int*a);
void maskDecoder(int *arrMask, int mask);
void netWork(int *ip, int *arrMask, int *netWork);
void wildCARD(int *arrMask, int *wildCard);
void broadCAST(int *arrMask, int *wildCard, int *broadCast);
void hostMIN(int *netWork, int *hostMin);
void hostMAX(int *broadCast, int *hostMax);
int hosTS(int *hostMin, int *hostMax);

int main() {
	setlocale(LC_ALL, "rus");
	int ip[4];
	char ipStr[15];
	int mask;
	int arrMask[4] = {};
	int netWORK[4];
	int wildCard[4];
	int broadCast[4];
	int hostMin[4];
	int hostMax[4];
	bool flag = true;

	do {
		cout << "Введите IP адрес:\n";
		cin >> ipStr;
		flag = verifySimbol(ipStr);
		if (flag) flag = stringIPtoARR(ipStr, ip);
		if (!flag) cout << "Adress not valid! Try again\n";
	} while (!flag);
	


	/*cout << "Введите IP адрес  (октэты вводятся в десятичной системе через Enter):\n";
	for (int i = 0; i < 4; i++) {
		int tmp;
		do {
			cin >> tmp;
			if (tmp < 0 || tmp > 255)cout << "Недопустимое значение! Введите еще раз: ";
		} while (tmp < 0 || tmp > 255);
		ip[i] = tmp;
	}*/
	cout << "Введите маску подсети /";
	do {
		cin >> mask;
		if (mask < 0 || mask > 32)cout << "Недопустимое значение! Введите еще раз /";
	} while (mask < 0 || mask > 32);
	cout << endl << "IP Adress: ";//9
	printROW(ip);
	cout << endl << "Bitmask:   " << mask << endl;//7
	maskDecoder(arrMask, mask);
	cout << "Netmask:   ";//7
	printROW(arrMask);
	cout << endl;
	wildCARD(arrMask, wildCard);
	cout << "Wildcard:  ";//8
	printROW(wildCard);
	cout << endl;

	netWork(ip, arrMask, netWORK);
	cout << "Network:   ";//7
	printROW(netWORK);
	cout << endl;

	broadCAST(netWORK, wildCard, broadCast);
	cout << "Broadcast: ";//9
	printROW(broadCast);
	cout << endl;

	hostMIN(netWORK, hostMin);
	cout << "Hostmin:   ";//7
	printROW(hostMin);
	cout << endl;

	hostMAX(broadCast, hostMax);
	cout << "Hostmax:   ";//7
	printROW(hostMax);
	cout << endl;

	cout << "Hosts:      " << hosTS(hostMin, hostMax) << endl;//5

	system("pause");
	return 0;
}


void printROW(int*a) {
	print10CC(a);
	cout << "    ";
	print2CC(a);
}
void print2CC(int *a) {
	for (int i = 0; i < 4; i++) {
		cout << bitset<4>(*(a + i) / 16) << " " << bitset<4>(*(a + i) % 16);
		if (i < 3) cout << ".";
	}

}
void print10CC(int *a) {
	for (int i = 0; i < 4; i++) {
		printf("%3d", *(a + i));
		if (i < 3) cout << ".";
	}

}
void maskDecoder(int *arrMask, int mask) {
	if (mask < 9) {
		*arrMask = 255;
		mask = 8 - mask;
		int deg = 1;
		while (mask) {
			*arrMask = *arrMask - deg;
			deg *= 2;
			mask--;
		}
		return;
	}
	if (mask < 17) {
		*arrMask = 255;
		*(arrMask + 1) = 255;
		mask = 16 - mask;
		int deg = 1;
		while (mask) {
			*(arrMask + 1) = *(arrMask + 1) - deg;
			deg *= 2;
			mask--;
		}
		return;
	}
	if (mask < 25) {
		*arrMask = 255;
		*(arrMask + 1) = 255;
		*(arrMask + 2) = 255;
		mask = 24 - mask;
		int deg = 1;
		while (mask) {
			*(arrMask + 2) = *(arrMask + 2) - deg;
			deg *= 2;
			mask--;
		}
		return;
	}

	*arrMask = 255;
	*(arrMask + 1) = 255;
	*(arrMask + 2) = 255;
	*(arrMask + 3) = 255;
	mask = 32 - mask;
	int deg = 1;
	while (mask) {
		*(arrMask + 3) = *(arrMask + 3) - deg;
		deg *= 2;
		mask--;
	}
	return;

}
void netWork(int *ip, int *arrMask, int *netWork) {
	for (int i = 0; i < 4; i++)*(netWork + i) = *(ip + i)&*(arrMask + i);
}
void wildCARD(int *arrMask, int *wildCard) {
	for (int i = 0; i < 4; i++)*(wildCard + i) = 255 - *(arrMask + i);
}

void broadCAST(int *arrMask, int *wildCard, int *broadCast) {
	for (int i = 0; i < 4; i++)*(broadCast + i) = *(arrMask + i) + *(wildCard + i);
}
void hostMIN(int *netWork, int *hostMin) {
	for (int i = 0; i <3; i++)*(hostMin + i) = *(netWork + i);
	*(hostMin + 3) = *(netWork + 3) + 1;
}
void hostMAX(int *broadCast, int *hostMax) {
	for (int i = 0; i <3; i++)*(hostMax + i) = *(broadCast + i);
	*(hostMax + 3) = *(broadCast + 3) - 1;
}

int hosTS(int *hostMin, int *hostMax) {
	int prod = 1;
	for (int i = 0; i < 3; i++) {

		prod *= *(hostMax + i) - *(hostMin + i) + 1;

	}
	prod *= *(hostMax + 3) - *(hostMin + 3) + 3;
	prod -= 2;
	return prod;
}
bool stringIPtoARR(char ipStr[], int *ip) {
	//char ipStr[] = "19.268.1.1";
	char oct1Str[3], oct2Str[3], oct3Str[3], oct4Str[3];
	bool flag = true;
	int oct1, oct2, oct3, oct4;
	int i = 0;
	while (*(ipStr + i) != '.') {
		*(oct1Str + i) = *(ipStr + i);
		i++;
	}
	i++;
	int j = 0;
	while (*(ipStr + i) != '.') {
		*(oct2Str + j++) = *(ipStr + i);
		i++;
	}
	i++;
	j = 0;
	while (*(ipStr + i) != '.') {
		*(oct3Str + j++) = *(ipStr + i);
		i++;
	}
	i++;
	j = 0;
	int tmp = strlen(ipStr);
	while (i < strlen(ipStr)) {
		*(oct4Str + j++) = *(ipStr + i);
		i++;
	}
	ip[0] = atoi(oct1Str);
	ip[1] = atoi(oct2Str);
	ip[2] = atoi(oct3Str);
	ip[3] = atoi(oct4Str);
	for (int i = 0; i < 4; i++) {
		if (ip[i] < 0 || ip[i]>255) return false;
	}
	return true;
}
bool verifySimbol(char strIP[]) {

	int i = 0, j = 0;
	bool flag = true;
	while (i < strlen(strIP))
	{
		if (*(strIP + i) < 46 || *(strIP + i) > 57 || *(strIP + i) == 47) {
			return false;			
		}
		if (j > 3) {
			return false;
		}
		if (*(strIP + i) == '.'&&*(strIP + i + 1) == '.') {
			return false;
		}
		j++;
		if (*(strIP + i) == '.') j = 0;
		i++;
	}

	return true;
}
