#define limite_caratteri 30

typedef struct {
	char tipo[limite_caratteri];
	int durata;
} abbonamento;

typedef struct {
	char nome[limite_caratteri];
	char cognome[limite_caratteri];
	int annodinascita;
	int id;
	abbonamento tipo_abbonamento;
} abbonato;
