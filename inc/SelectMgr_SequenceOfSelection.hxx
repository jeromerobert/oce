// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _SelectMgr_SequenceOfSelection_HeaderFile
#define _SelectMgr_SequenceOfSelection_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TCollection_BaseSequence_HeaderFile
#include <TCollection_BaseSequence.hxx>
#endif
#ifndef _Handle_SelectMgr_Selection_HeaderFile
#include <Handle_SelectMgr_Selection.hxx>
#endif
#ifndef _Handle_SelectMgr_SequenceNodeOfSequenceOfSelection_HeaderFile
#include <Handle_SelectMgr_SequenceNodeOfSequenceOfSelection.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Standard_NoSuchObject;
class Standard_OutOfRange;
class SelectMgr_Selection;
class SelectMgr_SequenceNodeOfSequenceOfSelection;



class SelectMgr_SequenceOfSelection  : public TCollection_BaseSequence {
public:

  void* operator new(size_t,void* anAddress) 
  {
    return anAddress;
  }
  void* operator new(size_t size) 
  {
    return Standard::Allocate(size); 
  }
  void  operator delete(void *anAddress) 
  {
    if (anAddress) Standard::Free((Standard_Address&)anAddress); 
  }

  
      SelectMgr_SequenceOfSelection();
  
  Standard_EXPORT     void Clear() ;
~SelectMgr_SequenceOfSelection()
{
  Clear();
}
  
  Standard_EXPORT    const SelectMgr_SequenceOfSelection& Assign(const SelectMgr_SequenceOfSelection& Other) ;
   const SelectMgr_SequenceOfSelection& operator =(const SelectMgr_SequenceOfSelection& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void Append(const Handle(SelectMgr_Selection)& T) ;
  
        void Append(SelectMgr_SequenceOfSelection& S) ;
  
  Standard_EXPORT     void Prepend(const Handle(SelectMgr_Selection)& T) ;
  
        void Prepend(SelectMgr_SequenceOfSelection& S) ;
  
        void InsertBefore(const Standard_Integer Index,const Handle(SelectMgr_Selection)& T) ;
  
        void InsertBefore(const Standard_Integer Index,SelectMgr_SequenceOfSelection& S) ;
  
  Standard_EXPORT     void InsertAfter(const Standard_Integer Index,const Handle(SelectMgr_Selection)& T) ;
  
        void InsertAfter(const Standard_Integer Index,SelectMgr_SequenceOfSelection& S) ;
  
  Standard_EXPORT    const Handle_SelectMgr_Selection& First() const;
  
  Standard_EXPORT    const Handle_SelectMgr_Selection& Last() const;
  
        void Split(const Standard_Integer Index,SelectMgr_SequenceOfSelection& Sub) ;
  
  Standard_EXPORT    const Handle_SelectMgr_Selection& Value(const Standard_Integer Index) const;
   const Handle_SelectMgr_Selection& operator()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
  Standard_EXPORT     void SetValue(const Standard_Integer Index,const Handle(SelectMgr_Selection)& I) ;
  
  Standard_EXPORT     Handle_SelectMgr_Selection& ChangeValue(const Standard_Integer Index) ;
    Handle_SelectMgr_Selection& operator()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}
  
  Standard_EXPORT     void Remove(const Standard_Integer Index) ;
  
  Standard_EXPORT     void Remove(const Standard_Integer FromIndex,const Standard_Integer ToIndex) ;





protected:





private:

  
  Standard_EXPORT   SelectMgr_SequenceOfSelection(const SelectMgr_SequenceOfSelection& Other);




};

#define SeqItem Handle_SelectMgr_Selection
#define SeqItem_hxx <SelectMgr_Selection.hxx>
#define TCollection_SequenceNode SelectMgr_SequenceNodeOfSequenceOfSelection
#define TCollection_SequenceNode_hxx <SelectMgr_SequenceNodeOfSequenceOfSelection.hxx>
#define Handle_TCollection_SequenceNode Handle_SelectMgr_SequenceNodeOfSequenceOfSelection
#define TCollection_SequenceNode_Type_() SelectMgr_SequenceNodeOfSequenceOfSelection_Type_()
#define TCollection_Sequence SelectMgr_SequenceOfSelection
#define TCollection_Sequence_hxx <SelectMgr_SequenceOfSelection.hxx>

#include <TCollection_Sequence.lxx>

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
