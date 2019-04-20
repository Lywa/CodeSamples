using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class MoveGalaxies : MonoBehaviour {
    GameObject galaxyCenter;
    //public Vector3 displacement = Vector3.zero;
    public float displacement;
    public float distance;

	// Use this for initialization
	void Start () {
        galaxyCenter = new GameObject();
        galaxyCenter.transform.localPosition = new Vector3(0, 5.18f,0);
	}
	
	// Update is called once per frame
    void Update () {
        Vector3 movement = (this.transform.localPosition - galaxyCenter.transform.localPosition);
        movement.Normalize();

        var currentDistance = this.transform.localPosition - galaxyCenter.transform.localPosition;
        //var newPosition = currentDistance.normalized * distance;
        //this.transform.localPosition = newPosition;

        if (displacement != 0f)
        {
            transform.Translate(movement * displacement, galaxyCenter.transform);
        }

        // Keyboard things
        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            transform.Translate(movement * 2, galaxyCenter.transform);
//            transform.Translate(Vector3.forward *10* Time.deltaTime);
            Debug.Log("right");
        }

        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            //transform.Translate(Vector3.back * 10 * Time.deltaTime);
            transform.Translate(movement * -2, galaxyCenter.transform);

            Debug.Log("left");
        }
        // End Keyboard things

    }
}
