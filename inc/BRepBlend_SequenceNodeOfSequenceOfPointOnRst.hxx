// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepBlend_SequenceNodeOfSequenceOfPointOnRst_HeaderFile
#define _BRepBlend_SequenceNodeOfSequenceOfPointOnRst_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_BRepBlend_SequenceNodeOfSequenceOfPointOnRst_HeaderFile
#include <Handle_BRepBlend_SequenceNodeOfSequenceOfPointOnRst.hxx>
#endif

#ifndef _BRepBlend_PointOnRst_HeaderFile
#include <BRepBlend_PointOnRst.hxx>
#endif
#ifndef _TCollection_SeqNode_HeaderFile
#include <TCollection_SeqNode.hxx>
#endif
#ifndef _TCollection_SeqNodePtr_HeaderFile
#include <TCollection_SeqNodePtr.hxx>
#endif
class BRepBlend_PointOnRst;
class BRepBlend_SequenceOfPointOnRst;



class BRepBlend_SequenceNodeOfSequenceOfPointOnRst : public TCollection_SeqNode {

public:

  
      BRepBlend_SequenceNodeOfSequenceOfPointOnRst(const BRepBlend_PointOnRst& I,const TCollection_SeqNodePtr& n,const TCollection_SeqNodePtr& p);
  
        BRepBlend_PointOnRst& Value() const;




  DEFINE_STANDARD_RTTI(BRepBlend_SequenceNodeOfSequenceOfPointOnRst)

protected:




private: 


BRepBlend_PointOnRst myValue;


};

#define SeqItem BRepBlend_PointOnRst
#define SeqItem_hxx <BRepBlend_PointOnRst.hxx>
#define TCollection_SequenceNode BRepBlend_SequenceNodeOfSequenceOfPointOnRst
#define TCollection_SequenceNode_hxx <BRepBlend_SequenceNodeOfSequenceOfPointOnRst.hxx>
#define Handle_TCollection_SequenceNode Handle_BRepBlend_SequenceNodeOfSequenceOfPointOnRst
#define TCollection_SequenceNode_Type_() BRepBlend_SequenceNodeOfSequenceOfPointOnRst_Type_()
#define TCollection_Sequence BRepBlend_SequenceOfPointOnRst
#define TCollection_Sequence_hxx <BRepBlend_SequenceOfPointOnRst.hxx>

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
