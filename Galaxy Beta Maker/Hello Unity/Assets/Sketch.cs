using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using Leap;
using System;
using UnityEngine.UI;

public class Sketch : MonoBehaviour {
	
	public GameObject myPrefab;
    Controller leapController;
    public GameObject DarkMatterTextField;

    public float totalDistance = 2.9f;
    public int totalCubes = 30;

    public List<MoveGalaxies> cubeList;

    private float lastKnownHandsDistance = 0.0f;

    private float matterCounter;

    // Use this for initialization
    void Start () {
        // Leap Motion things
        leapController = new Controller();
        leapController.EnableGesture(Gesture.GestureType.TYPE_SWIPE, true);
        SetText("", DarkMatterTextField);

        //LINEAR DISTRIBUTION
        /*for (int i = 0; i < totalCubes; i++) {

			float perc = i / (float)totalCubes;
			float x = perc*totalDistance;
			float y = 3.0f;
			float z = 0.0f;

			var newCube = (GameObject)Instantiate (myPrefab, new Vector3 (x, y, z), Quaternion.identity);
			newCube.GetComponent<CubeScript> ().SetSize (1.0f- perc);
			newCube.GetComponent<CubeScript> ().rotateSpeed = 0; // random.value;

		}*/

        Vector3 darkMatter = new Vector3(Input.mousePosition.x, Input.mousePosition.y, 0);
        // SIN DISTRIBUTION
        float darkMatterValue = (float)darkMatter.x;
        float universeDensity = (float)darkMatter.y;

		for (int i = 0; i < totalCubes; i++) {

			float perc = i / (float)totalCubes;

			float sin = Mathf.Sin (perc * Mathf.PI/2);
            //float x = 1.8f + sin * totalDistance + 0.001f * darkMatterValue;
            //float y = 5.0f + 0.001f * universeDensity;
            float x = 1.8f + sin * totalDistance;
            float y = 5.0f;
			float z = 0.0f;

			var newCube = (GameObject)Instantiate (myPrefab, new Vector3 (x, y, z), Quaternion.identity);
			newCube.GetComponent<CubeScript> ().SetSize (.45f* (1.0f- perc));
			newCube.GetComponent<CubeScript> ().rotateSpeed = 0.2f + perc*4.0f;
            // Add MoveGalaxies part of the Cube to a list that can be accessed later 
            cubeList.Add(newCube.GetComponent<MoveGalaxies>());

		}
	}


	// Update is called once per frame
	void Update () {
        var displacement = 0f; //Vector3.zero;
        var mapped_displacement = 0f;
        string swipeDirection = String.Empty;

        // Leap Motion things

        Frame leapFrame = leapController.Frame();
        if (leapFrame.Hands.Count == 2)
        {
            var handsDistance = GetHandsDistanceFromLeapMotion(leapFrame);
            var scaledHandsDistance = MapValueFloat(180f, 500f, 0f, 100f, handsDistance);
            displacement = GetExpansionValueFromLeapMotion(leapFrame);
            mapped_displacement = MapValueFloat(0f, 650f, 150f, 500f, displacement);
            mapped_displacement = displacement;

            if (displacement < 0) {
                // hands moving closer
                matterCounter += 5f * Math.Abs(mapped_displacement);
                matterCounter = 100-Math.Abs(scaledHandsDistance);
                if (matterCounter > 100f) matterCounter = 100f;
            }
            else if (displacement > 0) {
                //hands moving away
                matterCounter -= 5f * Math.Abs(mapped_displacement);
                matterCounter = 100-Math.Abs(scaledHandsDistance);

                if (matterCounter < 0f) matterCounter = 0f;
            }
            var darkMatterAmountText = String.Format(
                "{0:F0}", matterCounter
            );
            var textfield = "Hands dist: " + handsDistance + " scaledDistance: " + scaledHandsDistance + " matterCounter: " + matterCounter + " - displacement: " + displacement;
            Debug.Log(textfield);
            SetText(darkMatterAmountText, DarkMatterTextField);

        }
        else if (leapFrame.Hands.Count == 1)
        {
            swipeDirection = DetectSwipeDirection(leapFrame);

        }
        // end Leap Motion Things

        //Update all cubes
        foreach (MoveGalaxies cube in cubeList) {
            cube.displacement = displacement; // * -1.0f;

        }
        if (swipeDirection == "leftDisabled")
        {
            Debug.Log("Adding cube");
            for (int i = 0; i < 10; i++)
            {
                float perc = (float)cubeList.Count / ((float)cubeList.Count + 1);
                float x = 1.8f + Mathf.Sin(perc * Mathf.PI / 2) * totalDistance;
                float y = 5.0f;
                float z = 0.0f;
                float size = .45f * (1.0f + perc);
                size = cubeList[cubeList.Count - 1].transform.localScale.x;
                var newCube = (GameObject)Instantiate(myPrefab, new Vector3(x, y, z), Quaternion.identity);
                newCube.GetComponent<CubeScript>().SetSize(size);
                newCube.GetComponent<CubeScript>().rotateSpeed = 0.2f + perc * 4.0f;
                // Add MoveGalaxies part of the Cube to a list that can be accessed later 
                cubeList.Add(newCube.GetComponent<MoveGalaxies>());
            }
            Debug.Log(cubeList.Count);
        }

        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            //Add more objects
        }

        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            //Remove objects
        }

    }

    string DetectSwipeDirection(Frame leapFrame)
    {
        GestureList gestures = leapFrame.Gestures();
        string swipeDirection = "";

        foreach (Gesture gesture in gestures)
        {
//            Debug.Log("Gesture State: " + gesture.State);
            // check gesture detected
            if (gesture.State == Gesture.GestureState.STATE_STOP 
                && gesture.Type == Gesture.GestureType.TYPE_SWIPE)
            {
                SwipeGesture swipeGesture = new SwipeGesture(gesture);
                var isHorizontal = Math.Abs(swipeGesture.Direction.x) > Math.Abs(swipeGesture.Direction.y);
                if (isHorizontal)
                {
                    if (swipeGesture.Direction.x > 0)
                    {
                        Debug.Log("Swipe detected: RIGHT");
                        swipeDirection = "right";
                    }
                    else
                    {
                        Debug.Log("Swipe detected: LEFT");
                        swipeDirection = "left";
                    }
                }
            }
            else {
                //Debug.Log("Swipe detected: NONE");
                return "";
            }
        }

        return swipeDirection;
    }

    float GetHandsDistanceFromLeapMotion(Frame leapFrame) {
        var leftPosition = leapFrame.Hands.Leftmost.StabilizedPalmPosition;
        var rightPosition = leapFrame.Hands.Rightmost.StabilizedPalmPosition;

        var handsDistance = leftPosition.DistanceTo(rightPosition);

        return handsDistance;
    }

    float GetExpansionValueFromLeapMotion(Frame leapFrame)
    {
        float displacement;
        var leftPosition = leapFrame.Hands.Leftmost.StabilizedPalmPosition;
        var rightPosition = leapFrame.Hands.Rightmost.StabilizedPalmPosition;
        var leftVelocity = leapFrame.Hands.Leftmost.PalmVelocity;
        var rightVelocity = leapFrame.Hands.Rightmost.PalmVelocity;

        var handsDistance = leftPosition.DistanceTo(rightPosition);
        var handsDisplacement = handsDistance - lastKnownHandsDistance;
        lastKnownHandsDistance = handsDistance;

        if (leftVelocity.x < 0 && rightVelocity.x > 0)
        {
            //superpinch out / Expand galaxy
            //Debug.Log("Expanding");
            var v = leftVelocity.ToUnity();
            v.Normalize();
            displacement = Math.Abs(handsDisplacement) * Time.deltaTime;
        }
        else if (leftVelocity.x > 0 && rightVelocity.x < 0)
        {
            //superpinch in / Collapse galaxy
            //transform.Translate(, galaxyCenter.transform);
            //Debug.Log("Collapsing");
            var v = leftVelocity.ToUnity();
            v.Normalize();
            displacement = Math.Abs(handsDisplacement) * Time.deltaTime * -1;
        }
        else
            displacement = 0f; //Vector3.zero;

        Debug.Log("displacement=" + displacement + "; handsDistance=" + handsDistance + ";" + "handsDisplacement=" + handsDisplacement);

        var debugLine1 = "Distance L to R: " + leftPosition.DistanceTo(rightPosition);
        var debugLine2 = "Velocity. L: " + leftVelocity + " R: " + rightVelocity;
        return displacement;
    }


    public float MapValueFloat(float a0, float a1, float b0, float b1, float a)
    { 
        var value = b0 + (b1 - b0) * ((a - a0) / (a1 - a0));
        if (value < b0) value = b0;
        else if (value > b1) value = b1;
        return value;
    }

    private void SetText(String text, GameObject textField) {
        textField.GetComponent<Text>().text = text;
    }
}
