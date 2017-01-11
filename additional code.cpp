			// check if the half buffers are ready to be transferred to disk
			iStatus = DAQ_DB_HalfReady(1, &iHalfReadyDB, &iDAQstoppedDB);

/*			// check if the half buffers are ready to be transferred to disk
			iStatus = WFM_DB_HalfReady(2, iNumChans, piChanVect, &iHalfReady2);

			// check if the half buffers are ready to be transferred to disk
			iStatus = WFM_DB_HalfReady(3, iNumChans, piChanVect, &iHalfReady3);

			// check if the half buffers are ready to be transferred to disk
			iStatus = WFM_DB_HalfReady(4, iNumChans, piChanVect, &iHalfReady4);
*/

			if ( ( iHalfReadyDB == 1 ) && ( iStatus == 0 ) ){
/*				// timestamp
				sz_currentTime.Format("%d ", software_counter);
				sz_currentTime += "HalfReadyDB" + (currentTime.GetCurrentTime()).Format(" %H: %M: %S");
				sz_currentTime += "\n";
				fprintf(timeoutput, sz_currentTime);
				sz_currentTime.Empty();
*/
//				if ( ulCounterValue != positionCount ){		/* CURRENTLY TEMPORARY */
/*					// increment the software counter 
					positionCount = ulCounterValue;
					software_counter++;

					// assign current cpu clock time to finish (this is used to 
					// get the time duration of how long the cycles run so far have taken -
					// this value is then used to estimate how long rest of the test will
					// take)
					finish = clock();	

					// to estimate time and cycles left to complete the test
					TimeCalculate((float)(finish - start) / CLOCKS_PER_SEC,(int) software_counter); 
				} 
*/				
				// transfer the half buffer and convert to voltage values and print to file
				iStatus = DAQ_DB_Transfer(1, piHalfBufferDB, &ulPtsTfrDB, &iDAQstoppedDB);	iRetVal = NIDAQErrorHandler(iStatus, "DAQ_DB_Transfer",	 0);
				iStatus = DAQ_VScale(1, 1, 1, 1.0, 0.0, ulHalfBufferCount, piHalfBufferDB, pdVoltBufferDAQ);	iRetVal = NIDAQErrorHandler(iStatus, "DAQ_VScale", 0);	
				for (iDAQ = 0; iDAQ < 4320; iDAQ = iDAQ+12){
					fprintf(output, "%d %d %f %f %f %f %f %f %f %f %f %f %f %f\n", (int) software_counter, ((iDAQ/12)+1),
						pdVoltBufferDAQ [iDAQ], pdVoltBufferDAQ [iDAQ+1], pdVoltBufferDAQ [iDAQ+2], 
						pdVoltBufferDAQ [iDAQ+3], pdVoltBufferDAQ [iDAQ+4], pdVoltBufferDAQ [iDAQ+5], pdVoltBufferDAQ [iDAQ+6],
						pdVoltBufferDAQ [iDAQ+7], pdVoltBufferDAQ [iDAQ+8], pdVoltBufferDAQ [iDAQ+9], pdVoltBufferDAQ [iDAQ+10],
						pdVoltBufferDAQ [iDAQ+11]);
				}
		//		if ( ( iHalfReady2 == 1 ) || ( iHalfReady3 == 1 ) || ( iHalfReady4 == 1 ) )	{ /* CURRENTLY TEMPORARY */
					// read in new value for the output buffers for device 2, 3 and 4 as long as it is not the end of file
					// otherwise assign zeros to all output values
/*					for (i = 0; i < (int) ulHalfCount; i++){
						if ( ( (!feof(device2)) && (!feof(device3)) ) && (!feof(device4)) ){
							fscanf(device2, "%d", &pdBuffer2[i]);
							piHalfBuffer2[i] =  pdBuffer2[i];
							fscanf(device3, "%d", &pdBuffer3[i]);
							piHalfBuffer3[i] =  pdBuffer3[i];
							fscanf(device4, "%d", &pdBuffer4[i]);
							piHalfBuffer4[i] =  pdBuffer4[i];
						}
						else{
							piHalfBuffer2[i] =  0;
							piHalfBuffer3[i] =  0;
							piHalfBuffer4[i] =  0;
							
						}
					}
*/		//		}
				
			} else 
				iRetVal = NIDAQErrorHandler(iStatus, "DAQ_DB_HalfReady", 0);

			if ( ulCounterValue != positionCount ){
				// increment the software counter 
				positionCount = ulCounterValue;
				software_counter++;

				// assign current cpu clock time to finish (this is used to 
				// get the time duration of how long the cycles run so far have taken -
				// this value is then used to estimate how long rest of the test will
				// take)
				finish = clock();	

				// to estimate time and cycles left to complete the test
				TimeCalculate((float)(finish - start) / CLOCKS_PER_SEC,(int) software_counter); 
			} 

			// check if the half buffers are ready to be transferred to disk
			iStatus = WFM_DB_HalfReady(2, iNumChans, piChanVect, &iHalfReady2);

			if ( ( iHalfReady2 == 1 ) && ( iStatus == 0 ) ){
/*				// timestamp
				sz_currentTime.Format("%d ", software_counter);
				sz_currentTime += "HalfReady2" + (currentTime.GetCurrentTime()).Format(" %H: %M: %S");
				sz_currentTime += "\n";
				fprintf(timeoutput, sz_currentTime);
				sz_currentTime.Empty();
*/
				// read in new value for the output buffers for device 2 as long as it is not the end of file
				// otherwise assign zeros to all output values
				for (i = 0; i < (int) ulHalfCount; i++){
					if ( !feof(device2) ){
						fscanf(device2, "%d", &pdBuffer2[i]);
						piHalfBuffer2[i] =  pdBuffer2[i];
					}
					else{
						piHalfBuffer2[i] =  0;
					}
				}
				// load up the new values for the output buffers for device 2
				iStatus = WFM_DB_Transfer(2, iNumChans,  piChanVect, piHalfBuffer2, ulHalfCount);  iRetVal = NIDAQErrorHandler(iStatus,  "WFM_DB_Transfer2", iIgnoreWarning);
			} else
				iRetVal = NIDAQErrorHandler(iStatus,  "WFM_DB_HalfReady2", iIgnoreWarning);
			
			// check if the half buffers are ready to be transferred to disk
			iStatus = WFM_DB_HalfReady(3, iNumChans, piChanVect, &iHalfReady3);

			if ( ( iHalfReady3 == 1 ) && ( iStatus == 0 ) ){
/*				// timestamp
				sz_currentTime.Format("%d ", software_counter);
				sz_currentTime += "HalfReady3" + (currentTime.GetCurrentTime()).Format(" %H: %M: %S");
				sz_currentTime += "\n";
				fprintf(timeoutput, sz_currentTime);
				sz_currentTime.Empty();
*/
				// read in new value for the output buffers for device 3 as long as it is not the end of file
				// otherwise assign zeros to all output values
				for (i = 0; i < (int) ulHalfCount; i++){
					if ( !feof(device3) ){
						fscanf(device3, "%d", &pdBuffer3[i]);
						piHalfBuffer3[i] =  pdBuffer3[i];
					}
					else{
						piHalfBuffer3[i] =  0;
					}
				}
				// load up the new values for the output buffers for device 3
				iStatus = WFM_DB_Transfer(3, iNumChans,  piChanVect, piHalfBuffer3, ulHalfCount);  iRetVal = NIDAQErrorHandler(iStatus,  "WFM_DB_Transfer3", iIgnoreWarning);
			} else
				iRetVal = NIDAQErrorHandler(iStatus,  "WFM_DB_HalfReady3", iIgnoreWarning);

			// check if the half buffers are ready to be transferred to disk
			iStatus = WFM_DB_HalfReady(4, iNumChans, piChanVect, &iHalfReady4);

			if ( ( iHalfReady4 == 1 ) && ( iStatus == 0 ) ){
/*				// timestamp
				sz_currentTime.Format("%d ", software_counter);
				sz_currentTime += "HalfReady4" + (currentTime.GetCurrentTime()).Format(" %H: %M: %S");
				sz_currentTime += "\n";
				fprintf(timeoutput, sz_currentTime);
				sz_currentTime.Empty();
*/
				// read in new value for the output buffers for device 4 as long as it is not the end of file
				// otherwise assign zeros to all output values
				for (i = 0; i < (int) ulHalfCount; i++){
					if ( !feof(device4) ){
						fscanf(device4, "%d", &pdBuffer4[i]);
						piHalfBuffer4[i] =  pdBuffer4[i];
					}
					else{
						piHalfBuffer4[i] =  0;
					}
				}
				// load up the new values for the output buffers for device 4
				iStatus = WFM_DB_Transfer(4, iNumChans,  piChanVect, piHalfBuffer4, ulHalfCount);  iRetVal = NIDAQErrorHandler(iStatus,  "WFM_DB_Transfer4", iIgnoreWarning);
			} else
				iRetVal = NIDAQErrorHandler(iStatus,  "WFM_DB_HalfReady4", iIgnoreWarning);