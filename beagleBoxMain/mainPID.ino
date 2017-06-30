class PID{
	public:
	double error;
	double sample;
	double lastSample;
	double kP, kI, kD;      
	double P, I, D;
	double pid;
	double setPoint;
	long lastProcess;

	PID(double _kP, double _kI, double _kD){
		kP = _kP;
		kI = _kI;
		kD = _kD;
	}

	void addNewSample(double _sample){
			sample = _sample;
		}
	
	void setSetPoint(double _setPoint){
			setPoint = _setPoint;
		}

	double process(){
	// Implementação P ID
			error = setPoint - sample;
	float deltaTime = (millis() - lastProcess) / 1000.0;
			lastProcess = millis();
	//P
			P = error * kP;
	//I
			I = I + (error * kI) * deltaTime;
	//D
			D = (lastSample - sample) * kD / deltaTime;
			lastSample = sample;
	// Soma tudo
			pid = P + I + D;
	return pid;
		}
};


PID meuPid(1.0, 0, 0);
int sentido = 0;
bool anguloIncorreto = true;

// void setup() {
// 	Serial.begin(9600);
// 	pinMode(pSENSOR, INPUT);
// 	pinMode(pCONTROLE, OUTPUT);
// }

void controlePID(int valorDesejado) {
	
	Serial.print("In: controlePID\t");

	// Lê temperatura
	anguloIncorreto = true;

	while (anguloIncorreto){
		
		leituraOrientacao();
		double angulo = map(bussola, -180, 180, -10, 370);
		// Manda pro objeto PID!
		meuPid.addNewSample(angulo);
		meuPid.setSetPoint(valorDesejado); // Converte para controle
		

		sentido = meuPid.process();

		//velocidadeMotor = map(sentido + valorDesejado, -90, 90, 0 ,255);
		// Saída do controle
		if (sentido < -0.5){
			controle('a');
		}
		else if (sentido > 0.5){
			controle('d');
		}
		else {anguloIncorreto = false;}
	}
	
}



