// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ChFiDS_SequenceNodeOfSequenceOfSurfData_HeaderFile
#define _ChFiDS_SequenceNodeOfSequenceOfSurfData_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_ChFiDS_SequenceNodeOfSequenceOfSurfData_HeaderFile
#include <Handle_ChFiDS_SequenceNodeOfSequenceOfSurfData.hxx>
#endif

#ifndef _Handle_ChFiDS_SurfData_HeaderFile
#include <Handle_ChFiDS_SurfData.hxx>
#endif
#ifndef _TCollection_SeqNode_HeaderFile
#include <TCollection_SeqNode.hxx>
#endif
#ifndef _TCollection_SeqNodePtr_HeaderFile
#include <TCollection_SeqNodePtr.hxx>
#endif
class ChFiDS_SurfData;
class ChFiDS_SequenceOfSurfData;



class ChFiDS_SequenceNodeOfSequenceOfSurfData : public TCollection_SeqNode {

public:

  
      ChFiDS_SequenceNodeOfSequenceOfSurfData(const Handle(ChFiDS_SurfData)& I,const TCollection_SeqNodePtr& n,const TCollection_SeqNodePtr& p);
  
        Handle_ChFiDS_SurfData& Value() const;




  DEFINE_STANDARD_RTTI(ChFiDS_SequenceNodeOfSequenceOfSurfData)

protected:




private: 


Handle_ChFiDS_SurfData myValue;


};

#define SeqItem Handle_ChFiDS_SurfData
#define SeqItem_hxx <ChFiDS_SurfData.hxx>
#define TCollection_SequenceNode ChFiDS_SequenceNodeOfSequenceOfSurfData
#define TCollection_SequenceNode_hxx <ChFiDS_SequenceNodeOfSequenceOfSurfData.hxx>
#define Handle_TCollection_SequenceNode Handle_ChFiDS_SequenceNodeOfSequenceOfSurfData
#define TCollection_SequenceNode_Type_() ChFiDS_SequenceNodeOfSequenceOfSurfData_Type_()
#define TCollection_Sequence ChFiDS_SequenceOfSurfData
#define TCollection_Sequence_hxx <ChFiDS_SequenceOfSurfData.hxx>

#include <TCollection_SequenceNode.lxx>

#undef SeqItem
#undef SeqItem_hxx
#undef TCollection_SequenceNode
#undef TCollection_SequenceNode_hxx
#undef Handle_TCollection_SequenceNode
#undef TCollection_SequenceNode_Type_
#undef TCollection_Sequence
#undef TCollection_Sequence_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
