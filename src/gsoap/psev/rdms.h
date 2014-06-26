//gsoap ns service name: rdms
//gsoap ns service style: rpc
//gsoap ns service encoding: encoded
//gsoap ns service namespace: http://localhost/rdms.wsdl
//gsoap ns service location: http://localhost/rdms.cgi
//gsoap ns service executable: rdms.cgi

//gsoap ns schema namespace: urn:rdms


typedef unsigned short	xsd__u16;
typedef unsigned int xsd__u32;
typedef double xsd__double;
typedef bool xsd__bool;
typedef time_t xsd__time;
typedef int xsd__int;

typedef struct WEB_DOI
{
	xsd__u16	nStatID;	
	xsd__u16	nDevID;		
	xsd__u32	dCode;		
}WEB_DOI;


typedef struct WEB_DOIVAL
{
	WEB_DOI		doi;		

	xsd__u16	type;		
	xsd__u32	val;		
	xsd__double	dVal;		
	xsd__bool	bValid;		

	xsd__time	rvTime;		
}WEB_DOIVAL;

class ARR_WEB_DOI
{
	int			__size;
	WEB_DOI		*__ptr;

	ARR_WEB_DOI();
	ARR_WEB_DOI(struct soap*, int n);
	virtual ~ARR_WEB_DOI();
	int size();
	void resize(int n);
	WEB_DOI& operator[](int i) const;

	struct soap *soap;
};

class ARR_WEB_DOIVAL
{
	WEB_DOIVAL *__ptr;
	int __size;
	

	ARR_WEB_DOIVAL();
	ARR_WEB_DOIVAL(struct soap*, int n);
	virtual ~ARR_WEB_DOIVAL();
	int size();
	void resize(int n);
	WEB_DOIVAL& operator[](int i) const;
	
	struct soap *soap;
};

//////////////////////////////////////////////////////////////////////////
class vector
{
public:
	xsd__int *__ptr;
	int __size;
	struct soap *soap;
	vector();
	vector(int);
	virtual ~vector();
	void resize(int);
	int& operator[](int) const;
};

class matrix
{ 
public:
	vector *__ptr;
	int __size;
	struct soap *soap;
	matrix();
	matrix(int, int);
	virtual ~matrix();
	void resize(int, int);
	vector& operator[](int) const;
};



//gsoap rds service method-documentation: ns__GetData
int ns__GetData(WEB_DOI doi, WEB_DOIVAL *pVal);

int ns__GetDataN(ARR_WEB_DOI *doi, ARR_WEB_DOIVAL *pVal);

int ns__multi(int a, int b, int *c);

int ns__magic(xsd__int rank, matrix *result);