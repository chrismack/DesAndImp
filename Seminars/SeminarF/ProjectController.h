#pragma once
class ProjectController
{
public:
	ProjectController();
	~ProjectController();

	/*
	* Process the user input for the view menu
	*/
	void processViewOptinos();

	/*
	* Process the user input for the create media options
	*/
	void processCreateOptions();


	/*
	* Process the user input for the search option
	*/
	void processSearchOptions();

	/*
	* Process the user input for linking media together
	*/
	void processLinkingOptins();
};

