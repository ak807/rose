#ifndef RTEDSYM_H
#define RTEDSYM_H

bool RTEDDEBUG();

/* -----------------------------------------------------------
 * tps : 6March 2009: This class adds transformations
 * so that runtime errors are caught at runtime before they happen
 * -----------------------------------------------------------*/
struct RtedSymbols : AstSimpleProcessing {
	SgFunctionSymbol* roseCreateHeapArr;
	SgFunctionSymbol* roseCreateHeapPtr;
	SgFunctionSymbol* roseAccessHeap;
	SgFunctionSymbol* roseCheckpoint;
	SgFunctionSymbol* roseFunctionCall;
	SgFunctionSymbol* roseAssertFunctionSignature;
	SgFunctionSymbol* roseConfirmFunctionSignature;
	SgFunctionSymbol* roseFreeMemory;
	SgFunctionSymbol* roseReallocateMemory;
	SgFunctionSymbol* roseConvertIntToString;
	SgFunctionSymbol* roseCreateVariable;
	SgFunctionSymbol* roseCreateObject;
	SgFunctionSymbol* roseInitVariable;
	SgFunctionSymbol* roseMovePointer;
	SgFunctionSymbol* roseAccessVariable;
	SgFunctionSymbol* roseEnterScope;
	SgFunctionSymbol* roseExitScope;
	SgFunctionSymbol* roseIOFunctionCall;
	SgFunctionSymbol* roseRegisterTypeCall;
	SgFunctionSymbol* roseCheckIfThisNULL;

  // \todo add other rted runtime data structures
	SgClassSymbol*    roseTypeDesc;
	SgType*           size_t_member;

	RtedSymbols()
  : roseCreateHeapArr(NULL),
	  roseCreateHeapPtr(NULL),
    roseAccessHeap(NULL),
    roseCheckpoint(NULL),
    roseFunctionCall(NULL),
    roseAssertFunctionSignature(NULL),
    roseConfirmFunctionSignature(NULL),
    roseFreeMemory(NULL),
    roseReallocateMemory(NULL),
    roseConvertIntToString(NULL),
    roseCreateVariable(NULL),
    roseCreateObject(NULL),
    roseInitVariable(NULL),
    roseAccessVariable(NULL),
    roseEnterScope(NULL),
    roseExitScope(NULL),
    roseIOFunctionCall(NULL),
    roseRegisterTypeCall(NULL),
    roseCheckIfThisNULL(NULL),
		roseTypeDesc(NULL),
    size_t_member(NULL)
	{}

	// Traverse all nodes and check properties
	virtual void visit(SgNode* n) ;
};

#endif
