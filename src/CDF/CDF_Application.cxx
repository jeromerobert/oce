// File:	CDF_Application.cxx
// Created:	Fri Aug  8 07:49:46 1997
// Author:	Jean-Louis Frenkel
//		<rmi@frilox.paris1.matra-dtv.fr>
// Modified by rmi, Wed Jan 14 08:17:35 1998


#include <CDF_Application.ixx>
#include <Standard_ErrorHandler.hxx>
#include <TCollection_ExtendedString.hxx>
#include <Standard_ProgramError.hxx>
#include <Standard_GUID.hxx>
#include <CDM_MetaData.hxx>
#include <CDM_CanCloseStatus.hxx>
#include <CDF_Session.hxx>
#include <CDF_Directory.hxx>
#include <CDF_MetaDataDriver.hxx>
#include <CDF_RetrievableStatus.hxx>
#include <PCDM_ReadWriter.hxx>
#include <PCDM_RetrievalDriver.hxx>
#include <PCDM_StorageDriver.hxx>
#include <PCDM_ReaderStatus.hxx>

#include <Plugin.hxx>
#include <UTL.hxx>

#include <CDF_Timer.hxx>

#define theMetaDataDriver CDF_Session::CurrentSession()->MetaDataDriver()


//=======================================================================
//function : 
//purpose  : 
//=======================================================================
CDF_Application::CDF_Application():myRetrievableStatus(CDF_RS_OK) {}

//=======================================================================
//function : Load
//purpose  : 
//=======================================================================
Handle(CDF_Application) CDF_Application::Load(const Standard_GUID& aGUID) {
  return Handle(CDF_Application)::DownCast(Plugin::Load(aGUID));
}

//=======================================================================
//function : Open
//purpose  : 
//=======================================================================
void CDF_Application::Open(const Handle(CDM_Document)& aDocument) {
  CDF_Session::CurrentSession()->Directory()->Add(aDocument);
  aDocument->Open(this);
  Activate(aDocument,CDF_TOA_New);
}

//=======================================================================
//function : CanClose
//purpose  : 
//=======================================================================
CDM_CanCloseStatus CDF_Application::CanClose(const Handle(CDM_Document)& aDocument) {
  return aDocument->CanClose();
}

//=======================================================================
//function : Close
//purpose  : 
//=======================================================================
void CDF_Application::Close(const Handle(CDM_Document)& aDocument) {
  CDF_Session::CurrentSession()->Directory()->Remove(aDocument);
  aDocument->Close();
}

//=======================================================================
//function : Retrieve
//purpose  : 
//=======================================================================
Handle(CDM_Document) CDF_Application::Retrieve(const TCollection_ExtendedString& aFolder, 
				     const TCollection_ExtendedString& aName, 
				     const Standard_Boolean UseStorageConfiguration) {
  TCollection_ExtendedString nullVersion;
  return Retrieve(aFolder,aName,nullVersion,UseStorageConfiguration);
}

//=======================================================================
//function : Retrieve
//purpose  : 
//=======================================================================
Handle(CDM_Document)  CDF_Application::Retrieve(const TCollection_ExtendedString& aFolder, 
				     const TCollection_ExtendedString& aName,
				     const TCollection_ExtendedString& aVersion,
				     const Standard_Boolean UseStorageConfiguration) {
#ifdef DEB
  CDF_Timer theTimer;
#endif

  Handle(CDM_MetaData) theMetaData; 
  
  if(aVersion.Length() == 0) 
    theMetaData=theMetaDataDriver->MetaData(aFolder,aName);
  else 
    theMetaData=theMetaDataDriver->MetaData(aFolder,aName,aVersion);

#ifdef DEB  
  theTimer.ShowAndRestart("Getting MetaData: ");
#endif

  CDF_TypeOfActivation theTypeOfActivation=TypeOfActivation(theMetaData);
  Handle(CDM_Document) theDocument=Retrieve(theMetaData,UseStorageConfiguration,Standard_False);

#ifdef DEB
  theTimer.ShowAndRestart("Creating Transient: ");
#endif

  CDF_Session::CurrentSession()->Directory()->Add(theDocument);
  Activate(theDocument,theTypeOfActivation);

#ifdef DEB
  theTimer.ShowAndStop("Activate: ");
#endif

  theDocument->Open(this);
  return theDocument;


}

//=======================================================================
//function : CanRetrieve
//purpose  : 
//=======================================================================
CDF_RetrievableStatus CDF_Application::CanRetrieve(const TCollection_ExtendedString& aFolder, const TCollection_ExtendedString&  aName) {
 TCollection_ExtendedString aVersion;
 return CanRetrieve(aFolder,aName,aVersion);
}

//=======================================================================
//function : CanRetrieve
//purpose  : 
//=======================================================================
CDF_RetrievableStatus CDF_Application::CanRetrieve(const TCollection_ExtendedString&  aFolder, const TCollection_ExtendedString&  aName, const TCollection_ExtendedString&  aVersion) {
  
#ifdef DEB
  CDF_Timer theTimer;
#endif

  if (!theMetaDataDriver->Find(aFolder,aName,aVersion))
    return CDF_RS_UnknownDocument;
  else if (!theMetaDataDriver->HasReadPermission(aFolder,aName,aVersion))
    return CDF_RS_PermissionDenied;
  else {
#ifdef DEB
    theTimer.ShowAndRestart("theMetaDataDriver->Find: ");
#endif

    Handle(CDM_MetaData) theMetaData = theMetaDataDriver->MetaData(aFolder,aName,aVersion);

#ifdef DEB
    theTimer.ShowAndStop("Getting MetaData: ");
#endif

    if(theMetaData->IsRetrieved()) {
      return theMetaData->Document()->IsModified()
	? CDF_RS_AlreadyRetrievedAndModified : CDF_RS_AlreadyRetrieved;
    }
    else {
      TCollection_ExtendedString theFileName=theMetaData->FileName();
      TCollection_ExtendedString theFormat=PCDM_ReadWriter::FileFormat(theFileName);
      if(theFormat.Length()==0) {
	TCollection_ExtendedString ResourceName=UTL::Extension(theFileName);
	ResourceName+=".FileFormat";
	if(UTL::Find(Resources(),ResourceName))  {
	  theFormat=UTL::Value(Resources(),ResourceName);
	}
	else
	  return CDF_RS_UnrecognizedFileFormat;
      }
      if(!FindReaderFromFormat(theFormat)) return CDF_RS_NoDriver;
    }
  }
  return CDF_RS_OK;
  
}



//=======================================================================
//function : Activate
//purpose  : 
//=======================================================================
//void CDF_Application::Activate(const Handle(CDM_Document)& aDocument,const CDF_TypeOfActivation aTypeOfActivation) {
void CDF_Application::Activate(const Handle(CDM_Document)& ,const CDF_TypeOfActivation ) {
}

//=======================================================================
//function : DefaultFolder
//purpose  : 
//=======================================================================
Standard_ExtString CDF_Application::DefaultFolder(){
  if(myDefaultFolder.Length() == 0) {
    myDefaultFolder=CDF_Session::CurrentSession()->MetaDataDriver()->DefaultFolder();
  }
  return myDefaultFolder.ToExtString();
}

//=======================================================================
//function : SetDefaultFolder
//purpose  : 
//=======================================================================
Standard_Boolean CDF_Application::SetDefaultFolder(const Standard_ExtString aFolder) {
  Standard_Boolean found = CDF_Session::CurrentSession()->MetaDataDriver()->FindFolder(aFolder);
  if(found) myDefaultFolder=aFolder;
  return found;
}

//=======================================================================
//function : DefaultExtension
//purpose  : 
//=======================================================================
Standard_ExtString CDF_Application::DefaultExtension() {
  static TCollection_ExtendedString theDefaultExtension;
  theDefaultExtension="*";
  TColStd_SequenceOfExtendedString theFormats;
  Formats(theFormats);
  
  for (Standard_Integer i=1; i<= theFormats.Length(); i++) {
    TCollection_ExtendedString theResource(theFormats(i));
    theResource+=".FileExtension";
    if(UTL::Find(Resources(),theResource)) {
      theDefaultExtension=UTL::Value(Resources(),theResource);
      return theDefaultExtension.ToExtString();
    }
  }
  return theDefaultExtension.ToExtString();
}

//=======================================================================
//function : Retrieve
//purpose  : 
//=======================================================================
Handle(CDM_Document) CDF_Application::Retrieve(const Handle(CDM_MetaData)& aMetaData,const Standard_Boolean UseStorageConfiguration) {
  return Retrieve(aMetaData,UseStorageConfiguration,Standard_True);
} 

//=======================================================================
//function : ConvertStatus
//purpose  : 
//=======================================================================
static CDF_RetrievableStatus ConvertStatus(const PCDM_ReaderStatus theStatus) {
  CDF_RetrievableStatus aStatus;
  switch(theStatus) {
  case PCDM_RS_OK:
    aStatus=CDF_RS_OK;
    break;
  case PCDM_RS_NoDriver:
    aStatus=CDF_RS_NoDriver;
    break;
  case PCDM_RS_UnknownFileDriver:
    aStatus=CDF_RS_UnknownFileDriver;
    break;
  case PCDM_RS_OpenError:
    aStatus=CDF_RS_OpenError;
    break;
  case PCDM_RS_NoVersion:
    aStatus=CDF_RS_NoVersion;
    break;
  case PCDM_RS_NoSchema:
    aStatus=CDF_RS_NoSchema;
    break;
  case PCDM_RS_NoDocument:
    aStatus=CDF_RS_NoDocument;
    break;
  case PCDM_RS_ExtensionFailure:
    aStatus=CDF_RS_ExtensionFailure;
    break;
  case PCDM_RS_WrongStreamMode:
    aStatus=CDF_RS_WrongStreamMode;
    break;
  case PCDM_RS_FormatFailure:
    aStatus=CDF_RS_FormatFailure;
    break;
  case PCDM_RS_TypeFailure:
    aStatus=CDF_RS_TypeFailure;
    break;
  case PCDM_RS_TypeNotFoundInSchema:
    aStatus=CDF_RS_TypeNotFoundInSchema;
    break;
  case PCDM_RS_UnrecognizedFileFormat:
    aStatus=CDF_RS_UnrecognizedFileFormat;
    break;
  case PCDM_RS_MakeFailure:
    aStatus=CDF_RS_MakeFailure;
    break;
  case PCDM_RS_PermissionDenied:
    aStatus=CDF_RS_PermissionDenied;
    break;
  default:
    aStatus=CDF_RS_DriverFailure;    
  }
  return aStatus;
}

//=======================================================================
//function : Retrieve
//purpose  : 
//=======================================================================
Handle(CDM_Document) CDF_Application::Retrieve(const Handle(CDM_MetaData)& aMetaData,const Standard_Boolean UseStorageConfiguration, const Standard_Boolean IsComponent) {
  
  Handle(CDM_Document) theDocumentToReturn;
  myRetrievableStatus = CDF_RS_DriverFailure;
  if(IsComponent) {
    Standard_SStream aMsg;
    switch (CanRetrieve(aMetaData)) {
    case CDF_RS_UnknownDocument: 
      aMsg << "could not find the referenced document: " << aMetaData->Path() << "; not found."  <<(char)0 << endl;
      myRetrievableStatus = CDF_RS_UnknownDocument;
      Standard_Failure::Raise(aMsg);
      break;
    case CDF_RS_PermissionDenied:      
      aMsg << "Could not find the referenced document: " << aMetaData->Path() << "; permission denied. " <<(char)0 << endl;
      myRetrievableStatus = CDF_RS_PermissionDenied;
      Standard_Failure::Raise(aMsg);
      break;
    default:
      break;
    }
    
  }
  Standard_Boolean AlreadyRetrieved=aMetaData->IsRetrieved();
  if(AlreadyRetrieved) myRetrievableStatus = CDF_RS_AlreadyRetrieved;
  Standard_Boolean Modified=AlreadyRetrieved && aMetaData->Document()->IsModified();
  if(Modified) myRetrievableStatus = CDF_RS_AlreadyRetrievedAndModified;
  if(!AlreadyRetrieved || Modified) {

    Handle(PCDM_Reader) theReader=Reader(aMetaData->FileName());
    
    
    Handle(CDM_Document) theDocument;

    if(Modified)  {
      theDocument=aMetaData->Document();
      theDocument->RemoveAllReferences();
    }
    else
      theDocument=theReader->CreateDocument();
    
    SetReferenceCounter(theDocument,PCDM_RetrievalDriver::ReferenceCounter(aMetaData->FileName(), MessageDriver()));
    
    SetDocumentVersion(theDocument,aMetaData);
    theMetaDataDriver->ReferenceIterator()->LoadReferences(theDocument,aMetaData,this,UseStorageConfiguration);

    try {    
      OCC_CATCH_SIGNALS
      theReader->Read(aMetaData->FileName(),theDocument,this);
    } 
    catch (Standard_Failure) {
      PCDM_ReaderStatus aStatus = theReader->GetStatus();
      myRetrievableStatus = ConvertStatus(aStatus);
      if(myRetrievableStatus  > CDF_RS_AlreadyRetrieved){
	Standard_SStream aMsg;
	aMsg << Standard_Failure::Caught() << endl;
	Standard_Failure::Raise(aMsg);
      }	
    }
    PCDM_ReaderStatus aStatus = theReader->GetStatus();
    myRetrievableStatus = ConvertStatus(aStatus);
    
    theDocument->SetMetaData(aMetaData);

    theDocumentToReturn=theDocument;
  }
  else
    theDocumentToReturn=aMetaData->Document();
  
  return theDocumentToReturn;
}

//=======================================================================
//function : DocumentVersion
//purpose  : 
//=======================================================================
Standard_Integer CDF_Application::DocumentVersion(const Handle(CDM_MetaData)& theMetaData) {
//  const Handle(CDM_MessageDriver)& aMsgDriver = MessageDriver();
  return PCDM_RetrievalDriver::DocumentVersion(theMetaData->FileName(), MessageDriver());
}

//=======================================================================
//function : TypeOfActivation
//purpose  : 
//=======================================================================
CDF_TypeOfActivation CDF_Application::TypeOfActivation(const Handle(CDM_MetaData)& aMetaData) {

  if(aMetaData->IsRetrieved()) {
    Handle(CDM_Document) theDocument=aMetaData->Document();
    if(theDocument->IsOpened()) {
      if(theDocument->IsModified())
	return CDF_TOA_Modified;
      else
	return CDF_TOA_Unchanged;
    }
    
    else
      return CDF_TOA_New;
  }
  return CDF_TOA_New;
}


//=======================================================================
//function : FindReader
//purpose  : 
//=======================================================================
Standard_Boolean CDF_Application::FindReader(const TCollection_ExtendedString& aFileName) {
  Standard_GUID voidGUID;
  TCollection_ExtendedString voidResourceName;
  return FindReader(aFileName,voidGUID,voidResourceName);
}

//=======================================================================
//function : Reader
//purpose  : code dp
//=======================================================================
Handle(PCDM_Reader) CDF_Application::Reader (const TCollection_ExtendedString& aFileName) {
  TCollection_ExtendedString theFormat;
  if (!Format(aFileName,theFormat)) {
    Standard_SStream aMsg; 
    aMsg << "Could not found the format" <<(char)0;
    Standard_NoSuchObject::Raise(aMsg);

  }
  return ReaderFromFormat (theFormat);
}

//=======================================================================
//function : FindReaderFromFormat
//purpose  : 
//=======================================================================
Standard_Boolean CDF_Application::FindReaderFromFormat(const TCollection_ExtendedString& aFormat) {
  Standard_GUID voidGUID;
  TCollection_ExtendedString voidResourceName;
  return FindReaderFromFormat(aFormat,voidGUID,voidResourceName);
}


//=======================================================================
//function : ReaderFromFormat
//purpose  : 
//=======================================================================
Handle(PCDM_Reader) CDF_Application::ReaderFromFormat(const TCollection_ExtendedString& aFormat) {
  TCollection_ExtendedString UnfoundResourceName;
  Standard_GUID thePluginId;
  if(!FindReaderFromFormat(aFormat,thePluginId,UnfoundResourceName)) {
    Standard_SStream aMsg; 
    aMsg << "Could not found the item:" << UnfoundResourceName <<(char)0;
    myRetrievableStatus = CDF_RS_WrongResource;
    Standard_NoSuchObject::Raise(aMsg);
  } 
  Handle(PCDM_Reader) R;
  try {
    OCC_CATCH_SIGNALS
    R = Handle(PCDM_Reader)::DownCast(Plugin::Load(thePluginId));  
  } 
  catch (Standard_Failure) {
    myRetrievableStatus = CDF_RS_WrongResource;
    Standard_SStream aMsg;
    aMsg << Standard_Failure::Caught() << endl;
    Standard_Failure::Raise(aMsg);
  }	
  Handle(PCDM_RetrievalDriver) RD = Handle(PCDM_RetrievalDriver)::DownCast(R);
  if (!RD.IsNull()) {
    RD->SetFormat(aFormat);
    return RD;
  } else 
    myRetrievableStatus = CDF_RS_WrongResource;
  return R;
}

//=======================================================================
//function : FindReader
//purpose  : 
//=======================================================================
Standard_Boolean CDF_Application::FindReader(const TCollection_ExtendedString& aFileName, Standard_GUID& thePluginId, TCollection_ExtendedString& ResourceName) {
  
  TCollection_ExtendedString theFormat=PCDM_ReadWriter::FileFormat(aFileName);

// Si le format est dans le fichier, tant mieux. Sinon on se base sur l'extension.
  
  if(theFormat.Length()==0) {
    ResourceName=UTL::Extension(aFileName);
    ResourceName+=".FileFormat";
    
    if(UTL::Find(Resources(),ResourceName))  {
      theFormat=UTL::Value(Resources(),ResourceName);
    }
    else 
      return Standard_False;
  }
  return FindReaderFromFormat(theFormat,thePluginId,ResourceName);
}

//=======================================================================
//function : Format
//purpose  : dp 
//=======================================================================
Standard_Boolean CDF_Application::Format(const TCollection_ExtendedString& aFileName, 
					 TCollection_ExtendedString& theFormat)
{
  
  theFormat = PCDM_ReadWriter::FileFormat(aFileName);
  // Si le format est dans le fichier, tant mieux. Sinon on se base sur l'extension.
  if(theFormat.Length()==0) {
    TCollection_ExtendedString ResourceName;
    ResourceName=UTL::Extension(aFileName);
    ResourceName+=".FileFormat";
    
    if(UTL::Find(Resources(),ResourceName))  {
      theFormat = UTL::Value(Resources(),ResourceName);
    }
    else return Standard_False;
  }
  return Standard_True;
}

//=======================================================================
//function : FindReaderFromFormat
//purpose  : 
//=======================================================================
Standard_Boolean CDF_Application::FindReaderFromFormat(const TCollection_ExtendedString& aFormat, Standard_GUID& thePluginId, TCollection_ExtendedString& ResourceName) {
  
  ResourceName=aFormat;
  ResourceName+=".RetrievalPlugin";
  
  if(UTL::Find(Resources(),ResourceName))  {
    thePluginId=UTL::GUID(UTL::Value(Resources(),ResourceName));
    return Standard_True;
  }
  return Standard_False;
}

//=======================================================================
//function : CanRetrieve
//purpose  : 
//=======================================================================
CDF_RetrievableStatus CDF_Application::CanRetrieve(const Handle(CDM_MetaData)& aMetaData) {
  if(aMetaData->HasVersion())
    return CanRetrieve(aMetaData->Folder(),aMetaData->Name(),aMetaData->Version());
  else
    return CanRetrieve(aMetaData->Folder(),aMetaData->Name());
}
