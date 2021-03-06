#include "SQLite3UE4PluginPrivatePCH.h"
#include "Engine.h"
#include "CString.h"

static USQLiteDatabase* DatabasePtr = NewObject<USQLiteDatabase>();

//--------------------------------------------------------------------------------------------------------------

USQLiteBlueprintFunctionLibrary::USQLiteBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

//--------------------------------------------------------------------------------------------------------------

UObject* USQLiteBlueprintFunctionLibrary::NewObjectFromBlueprint(UObject* WorldContextObject, TSubclassOf<UObject> UC)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	UObject* tempObject = StaticConstructObject(UC);

	return tempObject;
}

//--------------------------------------------------------------------------------------------------------------

int32 USQLiteBlueprintFunctionLibrary::CastToInt(FString SQLiteResultValue)
{
	return FCString::Atoi(*SQLiteResultValue);
}

//--------------------------------------------------------------------------------------------------------------

int64 USQLiteBlueprintFunctionLibrary::CastToInt64(FString SQLiteResultValue)
{
	return FCString::Atoi64(*SQLiteResultValue);
}

//--------------------------------------------------------------------------------------------------------------

bool USQLiteBlueprintFunctionLibrary::CastToBoolean(FString SQLiteResultValue)
{
	return FCString::Atoi(*SQLiteResultValue) > 0;
}

//--------------------------------------------------------------------------------------------------------------

float USQLiteBlueprintFunctionLibrary::CastToFloat(FString SQLiteResultValue)
{
	return FCString::Atof(*SQLiteResultValue);
}

//--------------------------------------------------------------------------------------------------------------

double USQLiteBlueprintFunctionLibrary::CastToDouble(FString SQLiteResultValue)
{
	return FCString::Atod(*SQLiteResultValue);
}

//--------------------------------------------------------------------------------------------------------------

FSQLiteQueryTermExpectedNode USQLiteBlueprintFunctionLibrary::QueryStart(FSQLiteQueryTermExpectedNode LogicOperationOrNone)
{
	return FSQLiteQueryTermExpectedNode(LogicOperationOrNone.Query, TEXT("("));
}

//--------------------------------------------------------------------------------------------------------------

FSQLiteQueryLogicExpectedNode USQLiteBlueprintFunctionLibrary::QueryEnd(const FSQLiteQueryLogicExpectedNode& LastQueryTerm)
{
	return FSQLiteQueryLogicExpectedNode(LastQueryTerm.Query, TEXT(")"));
}

//--------------------------------------------------------------------------------------------------------------

FSQLiteQueryLogicExpectedNode USQLiteBlueprintFunctionLibrary::QueryTerm(const FSQLiteQueryTermExpectedNode& LogicOperation, FString Field, FString Operator, FString Value)
{
	return FSQLiteQueryLogicExpectedNode(LogicOperation.Query, FString::Printf(TEXT("%s %s \"%s\""), *Field, *Operator, *Value));
}

//--------------------------------------------------------------------------------------------------------------

FSQLiteQueryTermExpectedNode USQLiteBlueprintFunctionLibrary::QueryLogicAnd(const FSQLiteQueryLogicExpectedNode& LHS)
{
	return FSQLiteQueryTermExpectedNode(LHS.Query, TEXT(" AND "));
}

//--------------------------------------------------------------------------------------------------------------

FSQLiteQueryTermExpectedNode USQLiteBlueprintFunctionLibrary::QueryLogicOr(const FSQLiteQueryLogicExpectedNode& LHS)
{
	return FSQLiteQueryTermExpectedNode(LHS.Query, TEXT(" OR "));
}
//--------------------------------------------------------------------------------------------------------------

FSQLiteQueryFinalizedQuery USQLiteBlueprintFunctionLibrary::QueryFinal(const FSQLiteQueryLogicExpectedNode& QueryEndNode)
{
	return FSQLiteQueryFinalizedQuery(QueryEndNode.Query);
}