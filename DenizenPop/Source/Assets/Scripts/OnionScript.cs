using UnityEngine;
using System.Collections;

public class OnionScript : PowerUpScript {
	
	private MeatMonster refMeatMonster = null;
	
	// Use this for initialization
	new void Start () {
		base.Start ();
		refMeatMonster = GameObject.Find("MeatMonster").GetComponent<MeatMonster>();
	}
	
	void OnTriggerEnter(Collider tCollider)
	{
		if(tCollider.gameObject.name == "Horse" && refMeatMonster != null)
		{
			// speed up the Meat Monster
			refMeatMonster.OnionBoost();
			Destroy(this.gameObject);
		}
	}
}
