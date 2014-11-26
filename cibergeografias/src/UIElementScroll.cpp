#include "UIElementScroll.h"
#include <Rocket/Core.h>
#include <math.h>

UIElementScroll::UIElementScroll(const Rocket::Core::String& tag) :
Rocket::Core::Element(tag),
mContext(NULL),
mScrolling(false),
mMouseY(0),
mMouseDownY(0),
mMouseDownTime(0.0f),
mLastUpdate(0.0f),
mScrollValue(0.0f),
mScrollVelocity(0.0f)
{
	SetProperty("display", "block");
	SetProperty("overflow", "hidden");
	
	//lo cambi� yo, dec�a Nano::getTime
	mLastUpdate = ofGetElapsedTimeMillis();
}

UIElementScroll::~UIElementScroll()
{
	if (mContext)
	{
		//mContext->RemoveEventListener("mousedown", this);
		mContext->RemoveEventListener("mouseup", this);
		mContext->RemoveEventListener("mousemove", this);
	}
}

void UIElementScroll::registerWithlibRocket()
{
	Rocket::Core::Factory::RegisterElementInstancer("scroll", new Rocket::Core::ElementInstancerGeneric<UIElementScroll>());
}

void UIElementScroll::OnChildAdd(Rocket::Core::Element* child)
{
	if (child != this)
		return;
	
	// We need to attach at the global level to catch the mouse up
	// while the cursor is no longer over us
	mContext = GetContext();
	//mContext->AddEventListener("mousedown", this);
	mContext->AddEventListener("mouseup", this);
	mContext->AddEventListener("mousemove", this);
}

void UIElementScroll::ProcessEvent(Rocket::Core::Event& event)
{
	if (event.GetType() == "mousedown")
	{
		mFirstMove = true;
		/*mMouseY = event.GetParameter<float>("mouse_y", 0);
		mMouseDownY = mMouseY;
		mMouseDownTime = Rocket::Core::GetSystemInterface()->GetElapsedTime();
		mScrollVelocity = 0.0f;
		mScrollValue = 0.0f;
		ofLogNotice()<< "mouseDown " << mMouseY;*/

	}
	else if (mScrolling || mFirstMove)
	{
		if (event.GetType() == "mousemove")
		{
			if(mFirstMove){
				mMouseY = event.GetParameter<float>("mouse_y", 0);
				mMouseDownY = mMouseY;
				mMouseDownTime = Rocket::Core::GetSystemInterface()->GetElapsedTime();
				mScrollVelocity = 0.0f;
				mScrollValue = 0.0f;
				mFirstMove = false;
				mScrolling = true;
				//ofLogNotice()<< "mouseDown " << mMouseY;
			}else{
				int mouseY = event.GetParameter<float>("mouse_y", 0);
				int delta = mMouseY - mouseY;
				mMouseY = mouseY;

				SetScrollTop(GetScrollTop() + delta);
				event.StopPropagation();

				//ofLogNotice()<< "mouseMove " << mMouseY;
			}
		}
		else if (event.GetType() == "mouseup")
		{
			int mouseY = event.GetParameter<float>("mouse_y", 0);
			float deltaTime = Rocket::Core::GetSystemInterface()->GetElapsedTime() - mMouseDownTime;
			float velocity = (mMouseDownY - mouseY) / deltaTime;
			
			if (deltaTime < 1.0f && fabs(velocity) > 200.0f)
			{
                mScrollVelocity = velocity;
			}         
			
			mScrolling = false;
			event.StopPropagation();

			ofLogNotice()<< "mouseUp" ;
		}
	}
	
	Rocket::Core::Element::ProcessEvent(event);
}

void UIElementScroll::OnUpdate()
{
	float time = Rocket::Core::GetSystemInterface()->GetElapsedTime();
	float deltaTime = time - mLastUpdate;
	mLastUpdate = time;
	
	if (fabs(mScrollVelocity) < 0.01f)
	{      
		mScrollValue += mScrollVelocity * deltaTime;
		mScrollVelocity *= (1.0f - deltaTime) * 0.9f;
		
		if (fabs(mScrollVelocity) < 0.0001f)
		{
			mScrollVelocity = 0.0f;
		}      
		if (fabs(mScrollValue) > 1.0f)
		{
			int scrollAmount = (int)mScrollValue;
			SetScrollTop(GetScrollTop() + scrollAmount);
			mScrollValue -= (float)scrollAmount;
		}
	}
	
	Rocket::Core::Element::OnUpdate();
}
