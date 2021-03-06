// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _FEmTool_ListIteratorOfListOfVectors_HeaderFile
#define _FEmTool_ListIteratorOfListOfVectors_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _Handle_TColStd_HArray1OfReal_HeaderFile
#include <Handle_TColStd_HArray1OfReal.hxx>
#endif
#ifndef _Handle_FEmTool_ListNodeOfListOfVectors_HeaderFile
#include <Handle_FEmTool_ListNodeOfListOfVectors.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_NoMoreObject;
class Standard_NoSuchObject;
class FEmTool_ListOfVectors;
class TColStd_HArray1OfReal;
class FEmTool_ListNodeOfListOfVectors;



class FEmTool_ListIteratorOfListOfVectors  {
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

  
  Standard_EXPORT   FEmTool_ListIteratorOfListOfVectors();
  
  Standard_EXPORT   FEmTool_ListIteratorOfListOfVectors(const FEmTool_ListOfVectors& L);
  
  Standard_EXPORT     void Initialize(const FEmTool_ListOfVectors& L) ;
  
        Standard_Boolean More() const;
  
  Standard_EXPORT     void Next() ;
  
  Standard_EXPORT     Handle_TColStd_HArray1OfReal& Value() const;


friend class FEmTool_ListOfVectors;



protected:





private:



Standard_Address current;
Standard_Address previous;


};

#define Item Handle_TColStd_HArray1OfReal
#define Item_hxx <TColStd_HArray1OfReal.hxx>
#define TCollection_ListNode FEmTool_ListNodeOfListOfVectors
#define TCollection_ListNode_hxx <FEmTool_ListNodeOfListOfVectors.hxx>
#define TCollection_ListIterator FEmTool_ListIteratorOfListOfVectors
#define TCollection_ListIterator_hxx <FEmTool_ListIteratorOfListOfVectors.hxx>
#define Handle_TCollection_ListNode Handle_FEmTool_ListNodeOfListOfVectors
#define TCollection_ListNode_Type_() FEmTool_ListNodeOfListOfVectors_Type_()
#define TCollection_List FEmTool_ListOfVectors
#define TCollection_List_hxx <FEmTool_ListOfVectors.hxx>

#include <TCollection_ListIterator.lxx>

#undef Item
#undef Item_hxx
#undef TCollection_ListNode
#undef TCollection_ListNode_hxx
#undef TCollection_ListIterator
#undef TCollection_ListIterator_hxx
#undef Handle_TCollection_ListNode
#undef TCollection_ListNode_Type_
#undef TCollection_List
#undef TCollection_List_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
