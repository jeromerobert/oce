
#include <RWStepVisual_RWCompositeText.ixx>
#include <StepVisual_HArray1OfTextOrCharacter.hxx>
#include <StepVisual_TextOrCharacter.hxx>


#include <Interface_EntityIterator.hxx>


#include <StepVisual_CompositeText.hxx>


RWStepVisual_RWCompositeText::RWStepVisual_RWCompositeText () {}

void RWStepVisual_RWCompositeText::ReadStep
	(const Handle(StepData_StepReaderData)& data,
	 const Standard_Integer num,
	 Handle(Interface_Check)& ach,
	 const Handle(StepVisual_CompositeText)& ent) const
{


	// --- Number of Parameter Control ---

	if (!data->CheckNbParams(num,2,ach,"composite_text has not 2 parameter(s)")) return;

	// --- inherited field : name ---

	Handle(TCollection_HAsciiString) aName;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat1 =` not needed
	data->ReadString (num,1,"name",ach,aName);

	// --- own field : collectedText ---

	Handle(StepVisual_HArray1OfTextOrCharacter) aCollectedText;
	StepVisual_TextOrCharacter aCollectedTextItem;
	Standard_Integer nsub2;
	nsub2 = data->SubListNumber(num, 2, Standard_False);
	if (nsub2 !=0) {
	  Standard_Integer nb2 = data->NbParams(nsub2);
	  aCollectedText = new StepVisual_HArray1OfTextOrCharacter (1, nb2);
	  for (Standard_Integer i2 = 1; i2 <= nb2; i2 ++) {
	    //szv#4:S4163:12Mar99 `Standard_Boolean stat2 =` not needed
	    if (data->ReadEntity (nsub2,i2,"collected_text",ach,aCollectedTextItem))
	      aCollectedText->SetValue(i2,aCollectedTextItem);
	  }
	}
	else {
	  ach->AddFail("Parameter #2 (collected_text) is not a LIST");
	}

	//--- Initialisation of the read entity ---


	ent->Init(aName, aCollectedText);
}


void RWStepVisual_RWCompositeText::WriteStep
	(StepData_StepWriter& SW,
	 const Handle(StepVisual_CompositeText)& ent) const
{

	// --- inherited field name ---

	SW.Send(ent->Name());

	// --- own field : collectedText ---

	SW.OpenSub();
	for (Standard_Integer i2 = 1;  i2 <= ent->NbCollectedText();  i2 ++) {
	  SW.Send(ent->CollectedTextValue(i2).Value());
	}
	SW.CloseSub();
}


void RWStepVisual_RWCompositeText::Share(const Handle(StepVisual_CompositeText)& ent, Interface_EntityIterator& iter) const
{

	Standard_Integer nbElem1 = ent->NbCollectedText();
	for (Standard_Integer is1=1; is1<=nbElem1; is1 ++) {
	  iter.GetOneItem(ent->CollectedTextValue(is1).Value());
	}

}

