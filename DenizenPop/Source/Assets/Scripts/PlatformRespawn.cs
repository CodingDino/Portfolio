using UnityEngine;
using System.Collections;

public class PlatformRespawn : MonoBehaviour {
	
	GameObject horse_reference = null;
	private float despawn_offset = 3;
	private float respawn_offset = 5;
	private float spawn_random_range = 0.1f;
	private float gap_accel = 0.005f;		  // Change in gap width over time
	
	// PowerUp spawn rate
	private float onion_spawn_rate = 0.15f;
	private float hedge_spawn_rate = 0.15f;
	private float foal_spawn_rate = 0.15f;
	private float carrot_spawn_rate = 0.15f;
	private float bbq_spawn_rate = 0.15f;
	
	// Public
	public GameObject onion_prefab;
	public GameObject hedge_prefab;
	public GameObject foal_prefab;
	public GameObject carrot_prefab;
	public GameObject bbq_prefab;

	// Use this for initialization
	void Start () {
		horse_reference = GameObject.Find("Horse");
		
		// Determine which will spawn and add them to the prefab list
		if (Random.value < onion_spawn_rate)
			SpawnPowerUp(onion_prefab);
		if (Random.value < hedge_spawn_rate)
			SpawnPowerUp(hedge_prefab);
		if (Random.value < foal_spawn_rate)
			SpawnPowerUp(foal_prefab);
		if (Random.value < carrot_spawn_rate)
			SpawnPowerUp(carrot_prefab);
		if (Random.value < bbq_spawn_rate)
			SpawnPowerUp(bbq_prefab);
	}
	
	// Update is called once per frame
	void Update () {
		
		// Gap growth
		respawn_offset += gap_accel;
		
		//if (!renderer.isVisible && transform.position.x < horse_reference.transform.position.x-despawn_offset)
		if (transform.position.x < horse_reference.transform.position.x-despawn_offset)
			RespawnPlatform();
	}
	
	void RespawnPlatform()
	{
		// Move to new location
		float moveY = spawn_random_range /2 - Random.value*spawn_random_range;
		float moveX = despawn_offset+respawn_offset - Random.value*spawn_random_range;
		transform.Translate(moveX, moveY, 0.0f);//, Space.World);
		
		// Determine which will spawn and add them to the prefab list
		if (Random.value < onion_spawn_rate)
			SpawnPowerUp(onion_prefab);
		if (Random.value < hedge_spawn_rate)
			SpawnPowerUp(hedge_prefab);
		if (Random.value < foal_spawn_rate)
			SpawnPowerUp(foal_prefab);
		if (Random.value < carrot_spawn_rate)
			SpawnPowerUp(carrot_prefab);
		if (Random.value < bbq_spawn_rate)
			SpawnPowerUp(bbq_prefab);
	}
	
	void SpawnPowerUp(GameObject prefab)
	{
		float powerup_position_x = transform.position.x+0.5f*transform.localScale.x - Random.value*(transform.localScale.x-prefab.transform.localScale.x);
		float powerup_position_y = transform.position.y+0.5f*transform.localScale.y - prefab.transform.localScale.y/2;
		Vector3 powerup_position = new Vector3(powerup_position_x, powerup_position_y,0);
		Instantiate(prefab,powerup_position, Quaternion.identity);
	}
}
