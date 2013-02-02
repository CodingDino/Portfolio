using UnityEngine;
using System.Collections;

public class PowerUpScript : MonoBehaviour {
	
	protected GameObject horse_reference = null;
	private float despawn_offset = 3;
	private float respawn_offset = 5;
	//private float spawn_random_range = 0.1f;
	private float gap_accel = 0.005f;		  // Change in gap width over time

	// Use this for initialization
	protected void Start () {
		horse_reference = GameObject.Find("Horse");
	}
	
	// Update is called once per frame
	protected void Update () {
		
		// Gap growth
		respawn_offset += gap_accel;
		
		//if (!renderer.isVisible && transform.position.x < horse_reference.transform.position.x-despawn_offset)
		if (transform.position.x < horse_reference.transform.position.x-despawn_offset)
			KillPowerUp();
	}
	
	protected void KillPowerUp() {
		Destroy(gameObject);
	}
	
}

