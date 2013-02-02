using UnityEngine;
using System.Collections;

public class CarrotScript : PowerUpScript {
	
	public PlayerMovement horse = null;
	
	// Use this for initialization
	new void Start () {
		horse = GameObject.Find("Horse").GetComponent<PlayerMovement>();
		base.Start ();
	}
	
	void OnTriggerEnter(Collider tCollider)
	{
		if(tCollider.gameObject.name == "Horse" && horse)
		{
			// speed up the horse
			horse.CarrotBoost();
			Destroy(this.gameObject);
		}
	}
}
