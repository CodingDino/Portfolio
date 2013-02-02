using UnityEngine;
using System.Collections;

// Slow down on collision

public class HedgeSlowDown : PowerUpScript {
	
	private bool horse_hit = false;
	
	void OnTriggerEnter(Collider collider) {
		if(collider.gameObject.name == "Horse" && !horse_hit)
		{
			// slow the damn horse down
			horse_hit = true;
        	PlayerMovement horse_script = collider.gameObject.GetComponent<PlayerMovement>();
			horse_script.OnHedgeHit();
		}
	}
}
