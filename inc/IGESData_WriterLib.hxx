// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IGESData_WriterLib_HeaderFile
#define _IGESData_WriterLib_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_IGESData_NodeOfWriterLib_HeaderFile
#include <Handle_IGESData_NodeOfWriterLib.hxx>
#endif
#ifndef _Handle_IGESData_IGESEntity_HeaderFile
#include <Handle_IGESData_IGESEntity.hxx>
#endif
#ifndef _Handle_IGESData_ReadWriteModule_HeaderFile
#include <Handle_IGESData_ReadWriteModule.hxx>
#endif
#ifndef _Handle_IGESData_Protocol_HeaderFile
#include <Handle_IGESData_Protocol.hxx>
#endif
#ifndef _Handle_IGESData_GlobalNodeOfWriterLib_HeaderFile
#include <Handle_IGESData_GlobalNodeOfWriterLib.hxx>
#endif
#ifndef _Handle_Standard_Transient_HeaderFile
#include <Handle_Standard_Transient.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class IGESData_NodeOfWriterLib;
class Standard_NoSuchObject;
class IGESData_IGESEntity;
class IGESData_ReadWriteModule;
class IGESData_Protocol;
class IGESData_GlobalNodeOfWriterLib;
class Standard_Transient;



class IGESData_WriterLib  {
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

  
  Standard_EXPORT   static  void SetGlobal(const Handle(IGESData_ReadWriteModule)& amodule,const Handle(IGESData_Protocol)& aprotocol) ;
  
  Standard_EXPORT   IGESData_WriterLib(const Handle(IGESData_Protocol)& aprotocol);
  
  Standard_EXPORT   IGESData_WriterLib();
  
  Standard_EXPORT     void AddProtocol(const Handle(Standard_Transient)& aprotocol) ;
  
  Standard_EXPORT     void Clear() ;
  
  Standard_EXPORT     void SetComplete() ;
  
  Standard_EXPORT     Standard_Boolean Select(const Handle(IGESData_IGESEntity)& obj,Handle(IGESData_ReadWriteModule)& module,Standard_Integer& CN) const;
  
  Standard_EXPORT     void Start() ;
  
  Standard_EXPORT     Standard_Boolean More() const;
  
  Standard_EXPORT     void Next() ;
  
  Standard_EXPORT    const Handle_IGESData_ReadWriteModule& Module() const;
  
  Standard_EXPORT    const Handle_IGESData_Protocol& Protocol() const;





protected:





private:



Handle_IGESData_NodeOfWriterLib thelist;
Handle_IGESData_NodeOfWriterLib thecurr;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
