#include "Engine.h"

int main() {
	setlocale(LC_ALL, "Rus");
	Engine first_engine;
	double ambient_temp = 0.0;
	cout << "Введите значение температуры окружающей среды" << endl;
	cin >> ambient_temp;
	input(first_engine, 10, 110, 0.01, 0.0001, 0.1, { 20, 75, 100, 105, 75, 0 }, { 0, 75, 150, 200, 250, 300 }, 0, 0);
	if (Stand(first_engine, ambient_temp) == 1800) {
		cout << "Двигатель не перегрелся";
	} else {
		cout << "Двигатель перегреется через "<< Stand(first_engine, ambient_temp) << " сек";
	}
	return 0;
}

void input(Engine& first_engine, double nI, double overheatingT, double nHm, double nHv, double nC, vector<int> nstartM, vector<int> nstartV, double nM, double nV) {
	first_engine.I = nI;
	first_engine.overheatTemperature = overheatingT;
	first_engine.Hm = nHm;
	first_engine.Hv = nHv;
	first_engine.C = nC;
	first_engine.startM = nstartM;
	first_engine.startV = nstartV;
	first_engine.M = nM;
	first_engine.V = nV;
}

int Stand(Engine& first_engine, double ambient_temp) {
	int ptime = 0;
	int numberMV = 0;
	first_engine.M = first_engine.startM[numberMV];
	first_engine.V = first_engine.startV[numberMV];
	double engine_temp = ambient_temp;
	double a = first_engine.M / first_engine.I;
	double eps = first_engine.overheatTemperature - engine_temp;
	while (eps > ABSOLUTE_ERROR && ptime < MAX_TIME){
		ptime++;
		first_engine.V += a;
		if (numberMV < first_engine.startM.size() - 2)
			numberMV += first_engine.V < first_engine.startV[numberMV + 1] ? 0 : 1;
		double up = (first_engine.V - first_engine.startV[numberMV]);
		double down = (first_engine.startV[numberMV + 1] - first_engine.startV[numberMV]);
		double factor = (first_engine.startM[numberMV + 1] - first_engine.startM[numberMV]);
		first_engine.M = up / down * factor + first_engine.startM[numberMV];
		engine_temp += first_engine.getVc(ambient_temp, engine_temp) + first_engine.getVh();
		a = first_engine.M / first_engine.I;
		eps = first_engine.overheatTemperature - engine_temp;
	}
	return ptime;
}