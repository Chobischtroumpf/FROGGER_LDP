#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include <vector>
#include <string>

class MenuModel {
public:
    MenuModel();
    
	const std::vector<std::string>& getOptions() const;
    
	int getSelectedOption() const;
    
	void setSelectedOption(int option);
	
	bool isMenu = true;
	int selectedOption;
private:
	
    std::vector<std::string> options;
    
};

#endif // MENUMODEL_HPP