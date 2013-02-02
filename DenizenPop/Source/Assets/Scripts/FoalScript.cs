using UnityEngine;
using System.Collections;

public class FoalScript : PowerUpScript {
	
	private PlayerMovement pHorse = null;
	
	// Use this for initialization
	new void Start () {
		pHorse = GameObject.Find("Horse").GetComponent<PlayerMovement>();
		
		base.Start ();
	}
	
	void OnTriggerEnter(Collider tCollider)
	{
		if(tCollider.gameObject.name == "Horse" && pHorse)
		{
			// add something to the score!
			pHorse.FoalCollect();
			Destroy(this.gameObject);
		}
	}
}
