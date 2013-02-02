using UnityEngine;
using System.Collections;

public class MeatMonster : MonoBehaviour {
	
	// Sound
	SoundEffectHandler sound = null;
	
	private PlayerMovement	pHorse = null;
	
	private bool isBoosting = false;
	private float currentSpeed = 0;
	private int boostCount = 0;
	private float accel = 0.00167f;
	
	private bool started = false;
	
	// Use this for initialization
	void Start () {
		sound = GameObject.Find("SoundEffects").GetComponent<SoundEffectHandler>();
		pHorse = GameObject.Find("Horse").GetComponent<PlayerMovement>();
		currentSpeed = 1.0f;
	}
	
	// Update is called once per frame
	void FixedUpdate () {
		if(started)
		{
			// Base acceleration
			currentSpeed += accel;
			
			// Move based on currentSpeed
	    	transform.Translate(Vector3.right * currentSpeed * Time.deltaTime);
			
			// check for slowdown
			if(isBoosting)
			{
				boostCount++;
				if(boostCount > 180)
				{
					//stop boosting
					isBoosting = false;
					currentSpeed -=0.5f;
				}
			}
		}
	}
	
	// Update is called once per frame
	void Update () {
	}
	
	public void OnionBoost()
	{
		if(pHorse.IsStarted()) sound.onion_hit.Play ();
		
		// speed up temporarily
		if(!isBoosting)
		{
			isBoosting = true;
			boostCount = 0;
			currentSpeed+=0.5f;
		}
	}
	
	void OnTriggerEnter(Collider tCollider)
	{
		if(started)
		{
			if(tCollider.gameObject.name == "Horse")
			{
				// GAME OVER, MAN!
				//tCollider.gameObject.GetComponent("HorseMovement").GameOver();
				started = false;
				if(pHorse != null)
				{
					pHorse.GameFinished();
				}
			}
		}
	}
	
	public void GameStart()
	{
		started = true;
	}
	
	public void GameFinish()
	{
		started = false;
	}
}