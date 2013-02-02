using UnityEngine;
using System.Collections;

public class BBQJump : PowerUpScript {
	
	private PlayerMovement player_script_reference = null;
	
	new void Start () {
		base.Start ();
		player_script_reference = horse_reference.GetComponent<PlayerMovement>();
	}
	
	void OnTriggerEnter(Collider tCollider)
	{
		if(tCollider.gameObject.name == "Horse" && player_script_reference)
		{
			// make the damn horse jump
			player_script_reference.BounceHorse();
		}
	}
}
