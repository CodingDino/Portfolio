using UnityEngine;
using System.Collections;

public class PlayerMovement : MonoBehaviour {
	
	// Sound
	SoundEffectHandler sound = null;
	
	// Horizontal movement
	private float horse_speed = 1.0f;		// Automatic speed
	private float horse_movement = 1.5f;	// Player controlled speed
	private float horse_accel = 0.002f;	// Acceleration over time
	
	// Collision
	//private float colSpeed = 0.0f; // temp speed variable for dealing with collisions with vertical objects (walls, sides of platforms etc)
	
	// jumping
	private	bool carrotBoosted = false;
	private	int	carrotBoostCount = 0;
	private bool hedgeSlowed = false;
	private int hedgeSlowedCount = 0;
	
	private int jump_count = 2;
	private bool jump_held_down = false;
	private float jump_increase = 20f;
	private float jump_min = 1f;
	private float jump_max = 4f;
	private float jump_current = 1f;
	
	// Scoring
	public int score = 0;
	public static int[] high_scores = null;
	
	// Fail conditions
	private float fall_death_value = -2.5f;
	
	// States
	private bool started = false;
	private bool finished = false;
	
	// Particle Systems
	private ParticleSystem smokeParticle = null;
	private bool landed = false;
	private int smokeCount = 0;
	private	ParticleSystem boostParticle = null;
	private	ParticleSystem fireParticle = null;
	private bool burning = false;
	private int burnCount = 0;
	
	// References
	private	MeatMonster	mMonster = null;

	// Use this for initialization
	void Start () {
		sound = GameObject.Find("SoundEffects").GetComponent<SoundEffectHandler>();
		mMonster = GameObject.Find("MeatMonster").GetComponent<MeatMonster>();
		
		smokeParticle = GameObject.Find("SmokeParticle").GetComponent<ParticleSystem>();
		boostParticle = GameObject.Find("BoostParticle").GetComponent<ParticleSystem>();
		fireParticle = GameObject.Find("FireParticle").GetComponent<ParticleSystem>();
		
		Random.seed = (int)System.DateTime.Now.Ticks;
		
		if (high_scores == null)
		{
			high_scores = new int[10];
			for (int i=0; i < high_scores.Length; ++i)
			{
				high_scores[i] = 0;
			}
		}
	}
	
	// Update is called once per frame
	void Update () {
		
		if(started && !finished)
		{
			// Base acceleration
			horse_speed += horse_accel;
			
			// Move based on controls
			float moveX = Input.GetAxisRaw("Horizontal");
			if (Mathf.Abs(moveX) > 0.1f)
			{
		        float moveDelta = horse_movement * Time.deltaTime;
		        transform.Translate(moveX * moveDelta, 0, 0, Space.World);
		    }
			
			// Jump
			if (Input.GetButtonDown("Jump"))
			{
				if (jump_count > 0)
				{
					jump_held_down = true;
					if(IsStarted()) sound.jump_start.Play();
				}
			}
			if (jump_held_down)
			{
				jump_current += jump_increase * Time.deltaTime;
        		if (jump_current > jump_max)
				{
					jump_held_down = false;
					Jump(jump_max);
				}
			}
			if (Input.GetButtonUp("Jump"))
			{
				if (jump_count > 0 && jump_held_down)
				{
					Jump(jump_current);
				}
				jump_held_down = false;
			}
			
			// Move based on horse speed
	    	transform.Translate(Vector3.right * horse_speed * Time.deltaTime);
			if (!finished)
				score += 1;
			
		
			// Check if fell off bottom of screen
			// If below cut off y value...
			if(transform.position.y < fall_death_value)
			{
				// GAME OVER, MAN!
				mMonster.GameFinish();
				GameFinished();
				// Freeze camera
				transform.DetachChildren();
			}
		}
	}
	
	void FixedUpdate()
	{
		// Check for end of carrot boost/hedge slow
		if(carrotBoosted)
		{
			carrotBoostCount++;
			if(carrotBoostCount > 180)
			{
				horse_speed -= 0.25f;
				carrotBoosted = false;
				boostParticle.Stop();
			}
		}
		if(hedgeSlowed)
		{
			hedgeSlowedCount++;
			if(hedgeSlowedCount > 180)
			{
				horse_speed += 0.25f;
				hedgeSlowed = false;
			}
		}
		if(landed)
		{
			smokeCount++;
			if(smokeCount > 15)
			{
				smokeParticle.Stop();
				landed = false;
			}
		}
		if(burning)
		{
			burnCount++;
			if(burnCount > 60)
			{
				fireParticle.Stop();
				burning = false;
			}
		}
	}
	
	void Jump(float jump_height)
	{
		if(IsStarted()) sound.jump_release.Play();
		rigidbody.velocity = new Vector3(0.0f,jump_height,0.0f);
		jump_current = jump_min;
		--jump_count;
	}
	
	// On Collision Enter
    void OnCollisionEnter(Collision collision) {
        if (collision.gameObject.name == "Platform")
		{
			// we've hit a platform; figure out which facing we've hit
			
			// If the platform is below the horse
			var relativePosition = collision.contacts[0].normal;
			if (relativePosition.y > 0)
			{
				if(IsStarted()) sound.jump_land.Play();
				jump_count = 2;
				// play smoke for 0.5s
				smokeParticle.Play();
				smokeCount = 0;
				landed = true;
			}
			if(relativePosition.x+0.01 < 0 && gameObject.transform.position.x < collision.collider.gameObject.transform.position.x)
			{
				//game over
				finished = true;
				mMonster.GameFinish();
				GameFinished();
			}
		}
    }
	
	public void BounceHorse() {
		if(IsStarted()) sound.bbq_hit.Play ();
		// make the horse bounce!
		rigidbody.velocity = new Vector3(0.0f,jump_max,0.0f);
		jump_current = jump_min;
		jump_count = 0;
		//play fire particle
		fireParticle.Play();
		burning = true;
		burnCount = 0;
	}
	
	// On Trigger Exit
    void OnTriggerExit(Collider collider) {
    }
	
	// Called when hit by a hedge
	public void OnHedgeHit()
	{
		if(IsStarted()) sound.hedge_hit.Play ();
		if(!hedgeSlowed)
		{
			// slow the damn horse down
			horse_speed -= 0.25f;
		}
		hedgeSlowed = true;
		hedgeSlowedCount = 0;
	}
	
	public void CarrotBoost()
	{
		if(IsStarted()) sound.carrot_hit.Play();
		if(!carrotBoosted)
		{
			horse_speed += 0.25f;
		}
		carrotBoosted = true;
		carrotBoostCount = 0;
		// play BoostParticle
		boostParticle.Play();
	}
	
	public void FoalCollect()
	{
		if(IsStarted()) sound.foal_hit.Play();
		score += 100;
	}
	
	public int GetScore()
	{
		return score;
	}
	
	public void GameStarted()
	{
		finished = false;
		started = true;
	}
	
	public void GameFinished()
	{
		finished = true;
		
		if(IsStarted()) sound.whinny.Play();
		
		// Copy score into high scores
		if (score > high_scores[9])
		{
			high_scores[9] = score;
			System.Array.Sort (high_scores);
			System.Array.Reverse (high_scores);
		}
	}
	
	public bool IsStarted()
	{
		return started;
	}
	
	public bool IsFinished()
	{
		return finished;
	}
}
