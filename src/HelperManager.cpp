#include "HelperManager.h"
#include "Component.h"

void UIF::HelperManager::Invoke(UIF::Component* component, UIF::Window* window, UIF::Invoker invoker){
	for(auto* helper : this->helper_vec[component->Get_HVec_ID()].arr_vec[static_cast<long unsigned int>(invoker)]){
	helper->Execute(component, window);
	}
	//DFS, start Execution on Leaf
	if(invoker == UIF::Invoker::RESIZE){
		for(auto* child : component->Get_Children()){
			Invoke(child, window, invoker);
		}
	}
}

void UIF::HelperManager::Update(){
	this->notifications.Check(UIF::Data::DataLine::COMPONENT_LINE);
	this->notifications.Check(UIF::Data::DataLine::HELPER_LINE);

	for(auto& component : this->notifications.Read_Comp()){
		ArrOfVec arr_of_vec{};
		for(int idx{}; idx < arr_of_vec.arr_vec.size() - 1; idx++){
			arr_of_vec.arr_vec[idx] = invoker_helpers;
		}
		this->helper_vec.emplace_back(arr_of_vec);
		component->Set_HVec_ID(this->helper_vec.size() - 1);
	}
	for(auto& pkg: notifications.Read_Helper()){
		if(pkg.helper_op == UIF::Data::HelperOp::ADD_HELPER){
 			this->helper_vec[pkg.component->Get_HVec_ID()].arr_vec[static_cast<long unsigned int>(pkg.invoker)].emplace_back(this->lookup_helpers[pkg.helper]);
		}
		else{
			UIF::ContainerTargetErase(this->helper_vec[pkg.component->Get_HVec_ID()].arr_vec[static_cast<long unsigned int>(pkg.invoker)], this->lookup_helpers[pkg.helper]);
		}
	}
	this->notifications.Clear();
}
