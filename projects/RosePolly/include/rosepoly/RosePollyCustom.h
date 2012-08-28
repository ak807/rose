
#ifndef ROSE_POLLY_CUSTOM
#define ROSE_POLLY_CUSTOM

#include <rosepoly/access_pattern.h>

typedef struct fSpecs {
		string name;
		int num_args;
		IO * arg_spec;
		~fSpecs();
	} func_specs;

class RosePollyCustom {
	
protected:
	
	static vector<func_specs*> legalFuncs;		

	bool isAffineExpression( SgExpression * exp, const vector<string>& legalVars ) const;
	bool isIntExpression( SgExpression * exp ) const;
	
public:

	RosePollyCustom();
	virtual bool evaluate_loop( ForLoop * loop ) =0;
	virtual pollyDomain * add_loop( pollyDomain * d, ForLoop * loop ) const=0;
	
	virtual bool evaluate_conditional( Conditional * cond ) const=0;
	virtual pollyDomain * add_conditional( pollyDomain * d, Conditional * cond ) const=0;
	
	virtual bool evaluate_access( AccessPattern * ap ) const=0;
	virtual pollyMap * add_pattern( pollyDomain * m, AccessPattern * ap ) const=0;
	
	virtual void set_params( vector<string> p ) =0;

	virtual ~RosePollyCustom();

	friend void search_for_access_patterns( SgExpression * exp, vector<AccessPattern*>& pList, IO anIO );

};


class defaultRosePollyCustom : public RosePollyCustom {
	
	vector<string> legalVars;
	
public:
	
	virtual bool evaluate_loop( ForLoop * loop );
	virtual pollyDomain * add_loop( pollyDomain * d, ForLoop * loop ) const;
	
	virtual bool evaluate_conditional( Conditional * cond ) const;
	virtual pollyDomain * add_conditional( pollyDomain * d, Conditional * cond ) const;
	
	virtual bool evaluate_access( AccessPattern * ap ) const;
	virtual pollyMap * add_pattern( pollyDomain * m, AccessPattern * ap ) const;
	
	virtual void set_params( vector<string> p );
};

#endif


