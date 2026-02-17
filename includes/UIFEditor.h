#ifndef UIFEDITOR_H
#define UIFEDITOR_H

#include "UIFramework.h"

//Bulk of the code of the Editor UI
//Example of Lib use
namespace UIFEditor{
 

	

	void Configure(){

		//Abstract all of this away;
		UIF::Data::global_bus = new UIF::Data::GlobalBus();
		UIF::tex_cache = new UIF::TextureCache();
		UIF::WindowManager mgr;
		//Windows Here.
		mgr.Create_Window("UIFEditor", 1280, 720);	

		//Assets Here.	
		auto* f = UIF::Component::Create<UIF::Image>("Assets/582485.jpg", mgr["UIFEditor"])
			->Add_Helper(UIF::HelperType::SCALE_UNIFORM, UIF::Invoker::RESIZE)
			->Add_Helper(UIF::HelperType::DRAG, UIF::Invoker::LONG_CLICK);


		for(int x{}; x < 5; x++){
			f->Add_Child(UIF::Component::Create<UIF::Image>("Assets/582485.jpg", mgr["UIFEditor"])->
					Add_Helper(UIF::HelperType::SCALE_UNIFORM, UIF::Invoker::CLICK));

         	}


		mgr.Add_Component(f, mgr["UIFEditor"]);
	

		mgr.Run();

		delete UIF::Data::global_bus;
		delete UIF::tex_cache;
	}



};


#endif //UIFEDITOR_H
